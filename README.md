#Training repo

## Already Done
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

## TODO:
- Read & Learn about CMake
- In C language:
        - Read about ADT
        - Implement Stack exercise - Create "like stack class" with ADT - with numbers
        - Implement Stack exercise to be generic, with allocations. Use void** . Define the struct in the .c file. Expose only the void* in the .h file