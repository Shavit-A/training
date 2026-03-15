using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Grpc.Net.Client;
using GrpcLibraryConfigs;

using var channel = GrpcChannel.ForAddress("http://localhost:5022");
var client = new Library.LibraryClient(channel);

Console.WriteLine("--- Library Watcher ---");
Console.WriteLine("Connecting to server and waiting for new books...");

using var call = client.WatchBooks(new WatchBooksRequest());

try
{
    await foreach (var response in call.ResponseStream.ReadAllAsync())
    {
        Console.WriteLine($"[Update] (status: {response.Success}): [{response.BookId}] {response.Message}");
    }
}
catch (RpcException ex)
{
    Console.WriteLine($"gRPC Error: {ex.Status.Detail}");
}
catch (Exception ex)
{
    Console.WriteLine($"General Error: {ex.Message}");
}