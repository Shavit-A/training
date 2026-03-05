using Grpc.Net.Client;
using GrpcLibraryClient;

using var channel = GrpcChannel.ForAddress("https://localhost:7247");
var client = new Library.LibraryClient(channel);
var reply = await client.AddBookAsync(
    new Book { Id = 1, Title = "Title1", Author = "Author1", PublicationDate = 1234 });
Console.WriteLine($"Success status: {reply.Success}, Message: {reply.Message}");
