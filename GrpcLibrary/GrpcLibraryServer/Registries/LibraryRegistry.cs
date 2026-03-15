using GrpcLibraryConfigs;
using GrpcLibraryServer.Models;
using System.Collections.Concurrent;

namespace GrpcLibraryServer.Registries
{
    public class LibraryRegistry : ILibraryRegistry
    {
        private readonly ConcurrentDictionary<UInt32, Book> _books;
        public event Action<Book>? OnBookAdded;
        private UInt32 _idCounter;

        public LibraryRegistry()
        {
            _books = new ConcurrentDictionary<UInt32, Book>();
            _idCounter = 0;
        }

        public bool AddBook(string title, string author, UInt32 publicationDate)
        {
            UInt32 bookId = (UInt32)Interlocked.Increment(ref _idCounter);
            var newBook = new Book ( bookId, title, author, publicationDate );

            if (_books.TryAdd(bookId, newBook))
            {
                OnBookAdded?.Invoke(newBook);
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