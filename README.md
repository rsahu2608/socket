This is a multithreaded socket program to transfer files from client to server.
The server socket is capable of handeling multiple clients. Number of client to handel is also configurable. but at this point it is hardcoded.

Note that the client code is reading a hardcoded file, but we can have a mechanisum which can list the file names in a folder,
decide which files need to transfer by comparing the file modified time, and can transfer over socket.

We can also create a communication between client server like
  client -> server : send "file_name" as a string
  server can create an file with name "file_name"
  client->server : send all file data
  server: copy all the dat from socket to file.


Regarding the job run at a specific time:
  We can create a cron job in linux which will run the client and server program in the specific machines at specific time. That will do our job.
  


NOTE: I know this is not a fully functioning program for our requirement but yes we can enhance it to serve our job better.
