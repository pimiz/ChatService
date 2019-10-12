# ChatService
A simple C++ chat service consisting of client and server applications. Features a simple GUI for client. Built on Qt 5.10. Includes also some unit tests built on GTest. Needs a modern compiler (at least C++14).

- Cross-platform: Tested and working on Windows & Linux
- A client/server architecture utilized - one server instance can support multiple clients
- For flexibility and expandability, I created abstractions to the server side for server listener (AbstractServerListener) and for chat client (AbstractClient)
     - -> They act as abstract base classes for actual chat connections and clients, providing interfaces
     - -> Enables the service to support more than one protocols for creating chat connections (e.g. TCP, websockets…), however it should be connection-oriented/stateful
     - -> Chat clients and connections are managed through abstractions, hence the different types of chat connections can chat to each other with absolutely no need to know the connection types of each other
     - In this implementation only a TCP connection is used, but the service could easily be extended to support other connection means as well just by deriving from the abstraction classes
- On the client side the connection is also abstracted (AbstractChatConnection), which enables the possibility of implementing also other connections than TCP
- Factory pattern classes are used to create objects behind abstractions (connections and clients)
     - The factory is actually the only module which needs to know the actual connection type of the client

