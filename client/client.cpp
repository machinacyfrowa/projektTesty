#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
using namespace std;

int testFlag = 0;
int verboseFlag = 0;

void v(string s) {
	if(verboseFlag) fprintf(stdout, "%s\n", s.c_str());
}
void v(string s1, char* s2) {
	if(verboseFlag) fprintf(stdout, "%s %s\n", s1.c_str(), s2);
}
void executeTestCommand(string line) {
	switch(line.at(0)) {
		case 'c':
		v("Połączenie z xxx.");
		break;
		case 's':
		v("Wysyłanie xxx.");
		break;
		case 'q':
		v("Opuszczanie programu.");
		break;
		default:
		v("Nieprawidłowe polecenie w pliku tekstowym.");
		break;
	}
}

int main (int argc, char **argv)
{

	char *testFileName = NULL;
	char *outputFileName = NULL;
	
	int index, c, r;

	opterr = 0;

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
				executeTestCommand(line);
				r = rand() % 10 + 1;
				if(r % 2 == 0) outputFile << "PASS" << endl;
				else outputFile << "FAIL" << endl;
			}
	 		inputFile.close();
			outputFile.close();
		}
	}
	v("Koniec");
	return 0;
}
