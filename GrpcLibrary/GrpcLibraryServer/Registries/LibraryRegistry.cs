using System.Collections.Concurrent;
using GrpcLibraryServer.Models;

namespace GrpcLibraryServer.Registries
{
    public class LibraryRegistry : ILibraryRegistry
    {
        private readonly ConcurrentDictionary<UInt32, Book> _books;
        public event Action<Book>? OnBookAdded;

        public LibraryRegistry()
        {
            _books = new ConcurrentDictionary<UInt32, Book>();
        }

        public bool AddBook(Book book)
        {
            if (_books.TryAdd(book.Id, book))
            {
                OnBookAdded?.Invoke(book);
                return true;
            }
            return false;
        }

        public bool AddReviewToBook(UInt32 bookId, string review)
        {
            if (_books.TryGetValue(bookId, out var book))
            {
                book.AddReview(review);
                return true;
            }
            return false;
        }

        public bool RemoveBook(UInt32 bookId)
        {
            return _books.TryRemove(bookId, out _);
        }
    }
}
