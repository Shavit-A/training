using Grpc.Net.Client;
using GrpcLibraryClient;

using var channel = GrpcChannel.ForAddress("https://localhost:7247");
var client = new Library.LibraryClient(channel);

var addBookResponse= await client.AddBookAsync(
    new Book { Id = 1, Title = "Title1", Author = "Author1", PublicationDate = 1234 });
Console.WriteLine($"AddBook response - Success status: {addBookResponse.Success}, Message: {addBookResponse.Message}");

var AddReviewToBookResponse = await client.AddReviewToBookAsync(new AddReviewRequest { BookId = 1, ReviewText = "Very good!" });
Console.WriteLine($"Add Review To Book response - Success status: {AddReviewToBookResponse.Success}, Message: {AddReviewToBookResponse.Message}");

var RemoveBookResponse = await client.RemoveBookAsync(new RemoveBookRequest { BookId = 1 });
Console.WriteLine($"Remove Book response - Success status: {RemoveBookResponse.Success}, Message: {RemoveBookResponse.Message}");

using var call = client.BulkAddBooks();

for (uint i = 2; i < 5; i++)
{
    await call.RequestStream.WriteAsync(new Book { Id = i, Title = $"Title{i}", Author = $"Author{i}", PublicationDate = 1000 + i });
}

await call.RequestStream.CompleteAsync();

Console.WriteLine("Finished sending bulk of books. Waiting for response...");

var BulkAddBooksResponse = await call.ResponseAsync;
Console.WriteLine($"Bulk Add Books response - Success status: {BulkAddBooksResponse.Success}, Message: {BulkAddBooksResponse.Message}");
