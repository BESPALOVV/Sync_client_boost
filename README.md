# Sync_client_boost
The client synchronously communicates with the server, sends a request once every 1-7 seconds, each client has its own name, and requests a list of other clients if the server reports that the number of clients changes, the server is in another repository. One of the first works with Boost.Asio, in another repository will be asynchronous version of the client with the same functions.