using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using GrpcLibraryConfigs;
using GrpcLibraryServer.Registries;
using Microsoft.Win32;

namespace GrpcLibraryServer.Services
{
    public class LibraryService : Library.LibraryBase
    {
        private readonly ILogger<LibraryService> _logger;
        private readonly ILibraryRegistry _registry;

        public LibraryService(ILogger<LibraryService> logger, ILibraryRegistry registry)
        {
            _logger = logger;
            _registry = registry;
        }

        public override Task<Response> AddBook(
            Book request,
            ServerCallContext context)
        {
            _logger.LogInformation($"Add Book name: {request.Title}");

            var newBook = new Models.Book(
                request.Id, request.Title, request.Author, request.PublicationDate);
            bool isAdded = _registry.AddBook(newBook);

            return Task.FromResult(new Response
            {
                Success = isAdded,
                Message = isAdded ? "Book added successfully!" : $"Book with ID {request.Id} already exists."
            });
        }

        public override Task<Response> AddReviewToBook(
            AddReviewRequest request,
            ServerCallContext context)
        {
            _logger.LogInformation($"Add Review to Book ID: {request.BookId}");

            bool isReviewAdded = _registry.AddReviewToBook(request.BookId, request.ReviewText);

            return Task.FromResult(new Response
            {
                Success = isReviewAdded,
                Message = isReviewAdded ? "Review added successfully!" : $"Book with ID {request.BookId} not found."
            });
        }

        public override Task<Response> RemoveBook(
            RemoveBookRequest request,
            ServerCallContext context)
        {
            _logger.LogInformation($"Remove Book ID: {request.BookId}");
            bool isRemoved = _registry.RemoveBook(request.BookId);

            return Task.FromResult(new Response
            {
                Success = isRemoved,
                Message = isRemoved ? "Book removed successfully!" : $"Book with ID {request.BookId} not found."
            });
        }

        public override async Task<Response> BulkAddBooks(
            IAsyncStreamReader<Book> requestStream,
            ServerCallContext context)
        {
            _logger.LogInformation("Bulk Add Books started.");

            int count = 0;
            await foreach (var book in requestStream.ReadAllAsync())
            {
                var newBook = new Models.Book(book.Id, book.Title, book.Author, book.PublicationDate);
                if (_registry.AddBook(newBook))
                {
                    count++;
                }
            }

            _logger.LogInformation($"Bulk Add Books completed. Total books added: {count}.");
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

            _registry.OnBookAdded += bookHandler;

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
                _registry.OnBookAdded -= bookHandler;
            }
        }
    }
}