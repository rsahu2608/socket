// C program for the Client Side

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


// inet_addr
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

const int SIZE = 1024;

static int client_request = 0;

void send_file(FILE *fp, int sockfd)
{
 	int n;
  	char data[SIZE] = {0};

  	while(fgets(data, SIZE, fp) != NULL)
  	{
    	if (send(sockfd, data, sizeof(data), 0) == -1)
    	{
		  	perror("[-]Error in sending file.");
		  	exit(1);
    	}
    bzero(data, SIZE);
  	}	
}

// Driver Code
int main()
{
	// int network_socket;

	// Create a stream socket
	auto network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Initialise port number and address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(8989);

	// Initiate a socket connection
	int connection_status = connect(network_socket,
									(struct sockaddr*)&server_address,
									sizeof(server_address));

	// Check for connection error
	if (connection_status < 0) {
		puts("Error\n");
		return 0;
	}

	// printf("Connection established\n");
	std::cout << "Connection established\n";

	FILE *fp;
  	std::string filename("send.txt");
	fp = fopen(filename.c_str(), "r");
  	if (fp == NULL)
  	{
    	perror("[-]Error in reading file.");
    	exit(1);
 	}

  	send_file(fp, network_socket);
  	printf("[+]File data sent successfully.\n");



	// Send data to the socket
	//send(network_socket, &client_request, sizeof(client_request), 0);

	// Close the connection
	close(network_socket);

	return 0;
}

