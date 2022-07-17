This is a multithreaded socket program to transfer files from client to server.
The server socket is capable of handeling multiple clients. Number of client to handel is also configurable. but at this point it is hardcoded.

A cron job need to set as in cronjob.txt in client/server machines respectively. Bash script startServer.sh starts the server. startClient.sh goes to the location, list the "*.txt" (we can use any file types) in fileNames.txt, and then starts the client program.

**Client program:**
client reads the file fileNames.txt, loops through it to get the file names, transfers the files data to server.
We can have a mechanisum to decide which files need to transfer by comparing the file modified time, and can transfer over socket.

**Server program:**
Server will validate the client and accepts. Once the client socket is accepted it creates the thread to communicate with client for further file transfer, and waits to serve for other client request.
server is maintaining a vector of threads. When the thread count exceeds the max_count it waits for the threads to join. We can also implement the thread pool here to do the job.

**Load Scheduling**
We can have a request queue to manage the load the client request to server. When a client connect request comes, client information is stored in th equeue. Server can pick one client from the queue and process.

We can also create a communication between client server like
  client -> server : send "file_name" as a string
  server can create an file with name "file_name"
  client->server : send all file data
  server: copy all the dat from socket to file.


NOTE: I know this is not a fully functioning program for our requirement but yes we can enhance it to serve our job better.
