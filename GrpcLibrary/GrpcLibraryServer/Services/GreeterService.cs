using Grpc.Core;

namespace GrpcLibraryServer.Services
{
    public class LibraryService(ILogger<LibraryService> logger) : Library.LibraryBase
    {
        public override Task<HelloReply> SayHello(HelloRequest request, ServerCallContext context)
        {
            logger.LogInformation("The message is received from {Name}", request.Name);

            return Task.FromResult(new HelloReply
            {
                Message = "Hello " + request.Name
            });
        }
    }
}
