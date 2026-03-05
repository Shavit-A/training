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
    }
}