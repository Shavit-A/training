using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using GrpcLibraryConfigs;
using GrpcLibraryServer.Registries;

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

        public override Task<AddBookResponse> AddBook(
            AddBookRequest request,
            ServerCallContext context)
        {
            _logger.LogInformation($"Add Book name: {request.Title}");
            bool isAdded = _registry.AddBook(request.Title, request.Author, request.PublicationDate);

            return Task.FromResult(new AddBookResponse
            {
                Success = isAdded,
                Message = isAdded ? "Book added successfully!" : "Failed to add book"
            });
        }

        public override Task<AddReviewResponse> AddReviewToBook(
            AddReviewRequest request,
            ServerCallContext context)
        {
            _logger.LogInformation($"Add Review to Book ID: {request.BookId}");

            bool isReviewAdded = _registry.AddReviewToBook(request.BookId, request.ReviewText);

            return Task.FromResult(new AddReviewResponse
            {
                Success = isReviewAdded,
                Message = isReviewAdded ? "Review added successfully!" : $"Book with ID {request.BookId} not found."
            });
        }

        public override Task<RemoveBookResponse> RemoveBook(
            RemoveBookRequest request,
            ServerCallContext context)
        {
            _logger.LogInformation($"Remove Book ID: {request.BookId}");
            bool isRemoved = _registry.RemoveBook(request.BookId);

            return Task.FromResult(new RemoveBookResponse
            {
                Success = isRemoved,
                Message = isRemoved ? "Book removed successfully!" : $"Book with ID {request.BookId} not found."
            });
        }

        public override async Task<BulkAddBooksResponse> BulkAddBooks(
            IAsyncStreamReader<AddBookRequest> requestStream,
            ServerCallContext context)
        {
            _logger.LogInformation("Bulk Add Books started.");

            int count = 0;
            await foreach (var addBookRequest in requestStream.ReadAllAsync())
            {
                if (_registry.AddBook(addBookRequest.Title, addBookRequest.Author, addBookRequest.PublicationDate))
                {
                    count++;
                }
            }

            _logger.LogInformation($"Bulk Add Books completed. Total books added: {count}.");
            return new BulkAddBooksResponse
            {
                Success = true,
                Message = $"Bulk add completed. Total books added: {count}."
            };
        }

        public override async Task WatchBooks(
            WatchBooksRequest request,
            IServerStreamWriter<WatchBooksResponse> requestStream,
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
                    await requestStream.WriteAsync(new WatchBooksResponse
                    {
                        Success = true,
                        Message = $"New book [{book.Id}] Title: {book.Title}",
                        BookId = book.Id
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