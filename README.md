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
        * Add new book (via rpc)
        * Add comment to existing book (via rpc)
        * Remove book by ID (via rpc)
    - Implement client stream that will send new books for the server via streaming
    - Implement server stream that will update how is connedted every time new book is added