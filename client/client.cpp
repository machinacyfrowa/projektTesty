#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <string.h>
#define PORT 8080 
using namespace std;

int testFlag = 0;
int verboseFlag = 0;

void v(string s) {
	if(verboseFlag) fprintf(stdout, "%s\n", s.c_str());
}
void v(string s1, char* s2) {
	if(verboseFlag) fprintf(stdout, "%s %s\n", s1.c_str(), s2);
}
int main (int argc, char **argv)
{

	char *testFileName = NULL;
	char *outputFileName = NULL;
	
	int index, c, r;

	opterr = 0;

	struct sockaddr_in address; 
   	int sock = 0, valread; 
    	struct sockaddr_in serv_addr; 
   	char *hello = "Client test message"; 
   	char buffer[1024] = {0}; 
    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        	perror("Socket creation error: "); 
        	exit(EXIT_FAILURE);  
    	} 
	memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    	serv_addr.sin_family = AF_INET; 
    	serv_addr.sin_port = htons(PORT); 

	// Convert IPv4 and IPv6 addresses from text to binary form 
    	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  { 
        	perror("Invalid address/ Address not supported: "); 
        	exit(EXIT_FAILURE);  
    	} 
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
		perror("Connection failed: "); 
      		exit(EXIT_FAILURE);  
    	} 
	
	
	

	while( ( c = getopt(argc, argv, "t:o:v") ) != -1  )
		switch( c )
		{
			case 't':
			testFlag = 1;
			testFileName = optarg;
			break;
			case 'o':
			outputFileName = optarg;
			break;
			case 'v':
			verboseFlag = 1;
			break;
			case '?':
			if (optopt == 't')
          		fprintf (stderr, "Opcja -%c wymaga argumentu.\n", optopt);
        		else fprintf(stderr, "Nieznana opcja: -%c.\n", optopt);
			return 1;
			break;
			default:
			abort();
		}
	if(verboseFlag == 1){
		v("Ustawiono flagę \"gadatliwą\".");
		if(testFlag == 1) v("Ustawiono flagę testową");
		if(testFileName != NULL) v("Ustawiono plik z poleceniami testowymi", testFileName);
	}
	if(testFlag == 1) {
		//run automated tests based on file contents
		//open file first
		ifstream inputFile(testFileName);
		ofstream outputFile(outputFileName);
		if (inputFile.is_open()) {
			string line;
			srand (time(NULL));
    			while (getline(inputFile, line)) {
				string sts = line.substr(2, 1024);
				switch(line.at(0)) {
					case 'c':
						v("Połączenie z xxx.");
						break;
					case 's':
						v("Wysyłanie " + sts);
						send(sock , sts.c_str() , 1024 , 0 );
						break;
					case 'q':
						v("Opuszczanie programu.");
						break;
					default:
						v("Nieprawidłowe polecenie w pliku tekstowym.");
						break;
				}
			}
	 		inputFile.close();
			outputFile.close();
		}
	}
	send(sock , "" , strlen("") , 0 );
	v("Koniec");
	return 0;
}
