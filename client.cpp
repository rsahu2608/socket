#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>

using namespace std;

static int client_request = 0;

void send_file(string fileName, int sockfd)
{
	ifstream file (fileName.c_str(), ios::in | ios::binary | ios::ate);
	if (file.is_open())
	{
		auto size = file.tellg();
		auto memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

		if (send(sockfd, memblock, size, 0) == -1)
    	{
		  	cout << "Error in sending file.";
		  	return;
    	}
		delete[] memblock;
	}
  	else 
  	{
  		cout << "Unable to open file";
  	}
}

int main()
{
	auto network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// Initialise port number and address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(8989);

	// Initiate a socket connection
	int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));

	// Check for connection error
	if (connection_status < 0) 
	{
		cout << "Error in connection\n";
		return 0;
	}

	cout << "Connection established\n";

	// It is reading a hardcoded fine name here, we can have a mechanisum which can read the files in a folder
	// decide which files need to transfer by comparing the file modified time.
	string filename("send.txt");
  	send_file(filename, network_socket);
  	cout << "File data sent successfully.\n";

	// Send data to the socket
	//send(network_socket, &client_request, sizeof(client_request), 0);

	// Close the connection
	close(network_socket);

	return 0;
}

