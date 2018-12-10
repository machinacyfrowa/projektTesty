#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
	int testFlag = 0;
	char *testFileName = NULL;
	int verboseFlag = 0;
	int index, c;

	opterr = 0;

	while( ( c = getopt(argc, argv, "t:v") ) != -1  )
		switch( c )
		{
			case 't':
			testFlag = 1;
			testFileName = optarg;
			break;
			case 'v':
			verboseFlag = 1;
			break;
			case '?':
			if (optopt == 't')
          			fprintf (stderr, "Opcja -%c wymaga argumentu.\n", optopt);
        		else fprintf(stderr, "Nieznana opcja: -%c.\n", optopt);
			return 1;
			default:
			abort();
		}
	if(verboseFlag == 1){
		fprintf(stdout, "Ustawiono flagę gadatliwą.\n");
	}
	if(testFlag == 1){
		fprintf(stdout, "Ustawiono flagę testową, plik z poleceniami: %s.\n", testFileName);
	}
	fprintf(stdout, "Koniec\n");
}
