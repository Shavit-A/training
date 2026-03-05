using Grpc.Net.Client;
using GrpcLibraryClient;

// The port number must match the port of the gRPC server.
using var channel = GrpcChannel.ForAddress("https://localhost:7247");
var client = new Library.LibraryClient(channel);
var reply = await client.SayHelloAsync(
    new HelloRequest { Name = "LibraryClient" });
Console.WriteLine("Greeting: " + reply.Message);
Console.WriteLine("Press any key to exit...");
Console.ReadKey();