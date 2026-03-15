using GrpcLibraryConfigs;
using GrpcLibraryServer.Models;
using System;

namespace GrpcLibraryServer.Registries
{
    public interface ILibraryRegistry
    {
        event Action<Book>? OnBookAdded;

        bool AddBook(string title, string author, UInt32 publicationDate);
        bool AddReviewToBook(UInt32 bookId, string review);
        bool RemoveBook(UInt32 bookId);
    }
}
