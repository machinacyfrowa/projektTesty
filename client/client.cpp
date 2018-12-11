#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
using namespace std;

int main (int argc, char **argv)
{
	int testFlag = 0;
	char *testFileName = NULL;
	char *outputFileName = NULL;
	int verboseFlag = 0;
	int index, c;

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
		fprintf(stdout, "Ustawiono flagę gadatliwą.\n");
		if(testFlag == 1) fprintf(stdout, "Ustawiono flagę testową, plik z poleceniami: %s.\n", testFileName);
		if(outputFileName != NULL) fprintf(stdout, "Ustawiono plik wyjścia dla testów na: %s.\n", outputFileName);
	}
	if(testFlag == 1) {
		//run automated tests based on file contents
		//open file first
		ifstream file(testFileName);
		if (file.is_open()) {
			string line;
    		while (getline(file, line)) {
        	// using printf() in all tests for consistency
       		fprintf(stdout, "%s\n", line.c_str());
			}
	 		file.close();
		}
	}
	fprintf(stdout, "Koniec\n");
}
