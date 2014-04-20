#include "simple_compress.h"
#include <stdio.h>

#define MAXSIZE 1000

int main(void)
{
//	SimpleCompress sc("sample_log");
	SimpleCompress *sc;
	create_sc(&sc, "sample_log");

//	fstream fin("sample_input");
	FILE * fin = fopen("sample_input", "r");
//	string readLine;
	char readLine[MAXSIZE];
	int lineno = 1;
	while (fgets(readLine, MAXSIZE, fin)) {
//		cout << "Line: " << lineno << endl;
		printf("Line: %s\n", readLine);
//		sc.read_func(readLine);
		read_func(sc, readLine);
		write_or_compress(sc);
		lineno++;
	}
	delete_sc(sc);

	return 0;
}
