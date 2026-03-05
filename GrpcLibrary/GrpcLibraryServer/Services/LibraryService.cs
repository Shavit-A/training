using Grpc.Core;

namespace GrpcLibraryServer.Services
{
    public class LibraryService(ILogger<LibraryService> logger) : Library.LibraryBase
    {
        private static List<Models.Book> _books = new List<Models.Book>();

        public override Task<AddBookResponse> AddBook(Book request, ServerCallContext context)
        {
            logger.LogInformation($"The message is received, Book name: {request.Title}");

            var newBook = new Models.Book(request.Id, request.Title, request.Author, request.PublicationDate);
            _books.Add(newBook);

            return Task.FromResult(new AddBookResponse
            {
                Success = true,
                Message = "Book added successfully!"
            });
        }
    }
}
