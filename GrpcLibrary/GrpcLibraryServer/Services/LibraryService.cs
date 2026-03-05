using Grpc.Core;

namespace GrpcLibraryServer.Services
{
    public class LibraryService(ILogger<LibraryService> logger) : Library.LibraryBase
    {
        private static List<Models.Book> _books = new List<Models.Book>();

        public override Task<Response> AddBook(Book request, ServerCallContext context)
        {
            logger.LogInformation($"Add Book name: {request.Title}");

            var newBook = new Models.Book(request.Id, request.Title, request.Author, request.PublicationDate);
            _books.Add(newBook);

            return Task.FromResult(new Response
            {
                Success = true,
                Message = "Book added successfully!"
            });
        }

        public override Task<Response> AddReviewToBook(AddReviewRequest request, ServerCallContext context)
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

        public override Task<Response> RemoveBook(RemoveBookRequest request, ServerCallContext context)
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

        public override async Task<Response> BulkAddBooks(IAsyncStreamReader<Book> requestStream, ServerCallContext context)
        {
            logger.LogInformation("Bulk Add Books started.");

            int count = 0;
            await foreach (var book in requestStream.ReadAllAsync())
            {
                var newBook = new Models.Book(book.Id, book.Title, book.Author, book.PublicationDate);
                _books.Add(newBook);
                count++;
            }

            logger.LogInformation($"Bulk Add Books completed. Total books added: {count}.");
            return new Response
            {
                Success = true,
                Message = $"Bulk add completed. Total books added: {count}."
            };
        }
    }
}