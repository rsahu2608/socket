#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>
#include <vector>
#include <thread>
#include <chrono> 
#include <functional>
#include <cstring>


const int SIZE = 1024;

std::vector<std::thread> threads;
int tcount = 0;

void write_file(int sockfd)
{
	int n;
	FILE *fp;
	const std::string filename = "recv.txt";
	char buffer[SIZE];

	fp = fopen(filename.c_str(), "w");
	while (1) 
	{
		n = recv(sockfd, buffer, SIZE, 0);
		if (n <= 0)
		{
  			break;
		  	return;
		}
		std::cout << "data : " << buffer << std::endl;
		fprintf(fp, "%s", buffer);
		memset(buffer, SIZE, 0);
	}
	return;
}

int main()
{
	// Initialize variables
	int serverSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;

	socklen_t addr_size;
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8989);

	// Bind 
	bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	// Listen on the socket, with 50 max connection requests queued
	if (listen(serverSocket, 50) == 0)
		std::cout << "Listening\n";
	else
		std::cout << "Error\n";

	int i = 0;
	while (1) 
	{
		addr_size = sizeof(serverStorage);

		newSocket = accept(serverSocket, (struct sockaddr*)&serverStorage, &addr_size);
		int count = 0;
		
		//write_file(newSocket);
		
		// recv(newSocket, &count, sizeof(count), 0);

		// Create a function object
		/*std::function<void()> func = []() 
		{
            //Do Some Important Work
            std::cout << tcount++ << " readers coping the file....\n";
			std::cout << "From Thread ID : "<<std::this_thread::get_id() << "\n";
			std::this_thread::sleep_for (std::chrono::seconds(5));
			std::cout << tcount-- << " Reader is leaving";
        };
        */
        
        threads.push_back(std::thread(write_file, newSocket));
        
		if (threads.size() >= 5) 
		{
			for (std::thread& th : threads)
    		{
				// If thread Object is Joinable then Join that thread.
				if (th.joinable())
				    th.join();
    		}
		}
	}

	return 0;
}

