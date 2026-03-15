using GrpcLibraryServer.Models;

namespace GrpcLibraryServer.Registries
{
    public interface ILibraryRegistry
    {
        event Action<Book>? OnBookAdded;

        bool AddBook(Book book);
        bool AddReviewToBook(UInt32 bookId, string review);
        bool RemoveBook(UInt32 bookId);
    }
}
