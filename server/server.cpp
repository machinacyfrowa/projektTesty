/*
 * Serwer unix sockets
 * Paweł Zawadzki
 */
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <fstream>
#define PORT 8080 
using namespace std;

int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 

	//prepare log wile for write
	string log("output.log");	
	const char *logFileName = new char[log.length()];
	logFileName = log.c_str();
	ofstream logFile(logFileName);
	if(!logFile.is_open()) {
		perror("Opening log file failed: ");
		exit(EXIT_FAILURE);
	}
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
		perror("Creating socket file descriptor failed: "); 
		exit(EXIT_FAILURE); 
	} 
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
					&opt, sizeof(opt))) { 
		perror("Setting socket options failed: "); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
					sizeof(address))<0) { 
		perror("Binding socket failed: "); 
		exit(EXIT_FAILURE); 
	} 
	// listen on socket - maximum 3 waiting connections
	if (listen(server_fd, 3) < 0) { 
		perror("Listening on socket failed: "); 
		exit(EXIT_FAILURE); 
	} 
	// accept incomming connections
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) { 
		perror("Accepting connection failed: "); 
		exit(EXIT_FAILURE); 
	} 
	read(new_socket, buffer, 1024); 
	//repeat untill "" is sent
	while(1) {
		
		string lineContent(buffer);
		if(lineContent.length() > 1)
			lineContent = lineContent.substr(2, 1024);
		switch(buffer[0]) {
			case 's':
			logFile << "RCVD: " << lineContent << endl; 
			break;
			case 'p':
			//put file on server
			{
				char * outputFileName = new char[lineContent.length()+1];
				strcpy(outputFileName, lineContent.c_str());
				ofstream outputFileStream(outputFileName);
				if(outputFileStream) {
					logFile << "PFIL: " << outputFileName<< endl; 
					char * buffer = new char [1024];
					read(new_socket, buffer, 1024);
					outputFileStream << buffer;
					delete[] buffer;
					outputFileStream.close();
				}

			}
			break;
			case 'g':
			//get file from server
			{
				char * inputFileName = new char[lineContent.length()+1];
				strcpy(inputFileName, lineContent.c_str());
				ifstream inputFileStream(inputFileName);
				if(inputFileStream) {
					logFile << "GFIL: " << inputFileName<< endl; 

					inputFileStream.seekg(0, inputFileStream.end);
					int fileSize = inputFileStream.tellg();
					inputFileStream.seekg(0, inputFileStream.beg);
					char * buffer = new char [fileSize];
					inputFileStream.read(buffer, fileSize);
					
					send(new_socket, buffer, fileSize, 0);

					delete[] buffer;
					inputFileStream.close();

				}

				
			}
			break;
			case 'd':
			logFile << "DISC: " << endl; 
			close(new_socket);
			logFile.close();
			exit(EXIT_SUCCESS);
			break;		
			default:
			break;
			

		}

		
		bzero(buffer, 1024);
		read(new_socket , buffer, 1024); 
	}
	logFile.close();
	return 0; 
} 
