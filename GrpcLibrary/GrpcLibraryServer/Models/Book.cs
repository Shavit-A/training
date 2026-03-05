using System.Reflection;

namespace GrpcLibraryServer.Models
{
    public class Book
    {
        private readonly Int32 _id;
        private readonly string _title;
        private readonly string _author;
        private readonly UInt32 _publication_year;
        private List<string> _reviews;

        public Book(int id, string title, string author, UInt32 publication_year)
        {
            _id = id;
            _title = title;
            _author = author;
            _publication_year = publication_year;
            _reviews = new List<string>();
        }

        public void AddReview(string review)
        {
            _reviews.Add(review);
        }

        public string Titile => _title;
    }
}