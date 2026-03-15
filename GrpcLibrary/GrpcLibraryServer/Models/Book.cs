using System.Reflection;
using System.Collections.Concurrent;

namespace GrpcLibraryServer.Models
{
    public class Book
    {
        public UInt32 Id { get; }
        public string Title { get; }
        public string Author { get; }
        public UInt32 PublicationYear { get; }
        private readonly ConcurrentBag<string> _reviews;

        public Book(UInt32 id, string title, string author, UInt32 publication_year)
        {
            Id = id;
            Title = title;
            Author = author;
            PublicationYear = publication_year;
            _reviews = new ConcurrentBag<string>();
        }

        public void AddReview(string review)
        {
            _reviews.Add(review);
        }
    }
}