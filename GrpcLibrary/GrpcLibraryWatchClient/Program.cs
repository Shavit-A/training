using Google.Protobuf.WellKnownTypes;
using Grpc.Core;
using Grpc.Net.Client;
using GrpcLibraryWatchClient;

using var channel = GrpcChannel.ForAddress("https://localhost:7247");
var client = new Library.LibraryClient(channel);

Console.WriteLine("--- Library Watcher ---");
Console.WriteLine("Connecting to server and waiting for new books...");

using var call = client.WatchBooks(new Empty());

try
{
    await foreach (var response in call.ResponseStream.ReadAllAsync())
    {
        Console.WriteLine($"[Update] (status: {response.Success}): {response.Message}");
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