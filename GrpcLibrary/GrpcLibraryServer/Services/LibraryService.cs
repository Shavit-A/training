using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using System.Reflection.Metadata.Ecma335;

namespace GrpcLibraryServer.Services
{
    public class LibraryService(ILogger<LibraryService> logger) : Library.LibraryBase
    {
        private static List<Models.Book> _books = new List<Models.Book>();
        private static event Action<Models.Book>? _onBookAdded;

        private void AddBookAndNotify(Models.Book book)
        {
            _books.Add(book);
            _onBookAdded?.Invoke(book);
        }

        public override Task<Response> AddBook(
            Book request,
            ServerCallContext context)
        {
            logger.LogInformation($"Add Book name: {request.Title}");

            var newBook = new Models.Book(
                request.Id, request.Title, request.Author, request.PublicationDate);
            AddBookAndNotify(newBook);

            return Task.FromResult(new Response
            {
                Success = true,
                Message = "Book added successfully!"
            });
        }

        public override Task<Response> AddReviewToBook(
            AddReviewRequest request,
            ServerCallContext context)
        {
            logger.LogInformation($"Add Review to Book ID: {request.BookId}");

            var book = _books.FirstOrDefault(b => b.Id == request.BookId);
            if (book == null)
            {
                return Task.FromResult(new Response
                {
                    Success = false,
                    Message = "Book not found!"
                });
            }

            book.AddReview(request.ReviewText);
            return Task.FromResult(new Response
            {
                Success = true,
                Message = "Review added successfully!"
            });
        }

        public override Task<Response> RemoveBook(
            RemoveBookRequest request,
            ServerCallContext context)
        {
            logger.LogInformation($"Remove Book ID: {request.BookId}");
            var book = _books.FirstOrDefault(b => b.Id == request.BookId);
            if (book == null)
            {
                return Task.FromResult(new Response
                {
                    Success = false,
                    Message = "Book not found!"
                });
            }

            _books.Remove(book);
            return Task.FromResult(new Response
            {
                Success = true,
                Message = "Book removed successfully!"
            });
        }

        public override async Task<Response> BulkAddBooks(
            IAsyncStreamReader<Book> requestStream,
            ServerCallContext context)
        {
            logger.LogInformation("Bulk Add Books started.");

            int count = 0;
            await foreach (var book in requestStream.ReadAllAsync())
            {
                var newBook = new Models.Book(book.Id, book.Title, book.Author, book.PublicationDate);
                AddBookAndNotify(newBook);
                count++;
            }

            logger.LogInformation($"Bulk Add Books completed. Total books added: {count}.");
            return new Response
            {
                Success = true,
                Message = $"Bulk add completed. Total books added: {count}."
            };
        }

        public override async Task WatchBooks(
            Empty request,
            IServerStreamWriter<Response> responseStream,
            ServerCallContext context)
        {

            var channel = System.Threading.Channels.Channel.CreateUnbounded<Models.Book>();

            Action<Models.Book> bookHandler = (book) =>
            {
                channel.Writer.TryWrite(book);
            };

            _onBookAdded += bookHandler;

            try
            {
                await foreach (var book in channel.Reader.ReadAllAsync(context.CancellationToken))
                {
                    await responseStream.WriteAsync(new Response
                    {
                        Success = true,
                        Message = $"New book [{book.Id}] Title: {book.Title}"
                    });
                }
            }
            catch (OperationCanceledException)
            {
                Console.WriteLine("Client disconnected from watch stream.");
            }
            finally
            {
                _onBookAdded -= bookHandler;
            }
        }
    }
}