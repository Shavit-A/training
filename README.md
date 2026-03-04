#Training repo

## TODO:
- Read about Protobuf (rpc, working with streams)
- Read about grpc
## Implement exercise
# Client Server Library of books (C# language):
    - Each book will contain:
        * Title
        * Author
        * List of Comments
    - Functionalities:
        * Add new book (regular req response rpc)
        * Add comment to existing book (regular rpc)
        * Remove book by ID (regular rpc)
    - Implement client stream that will send new books for the server via streaming (server streaming rpc)
    - Implement server stream that will update how is connedted every time new book is added (client streaming rpc)
