/* 
 * Austin Zhang
 * 604736503
 * CS35L
 * trb2.c 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	
	int man;

	char curr;
	char array[1];
	char* from;
	char* to;
	
	size_t i;
	size_t j;
	size_t length;

	//lengths equal?
	if (length != strlen(to)) {
		//print error
		fprintf(stderr, "Lengths are not equal.");
		exit(1);
	}

	//number of arguments correct?
	if (argc != 3) {
		//print error
		fprintf(stderr, "Argument count incorrect.");
		exit(1);
	}

	from = argv[1];
	to = argv[2];
	length = strlen(from);

	//duplicates in 'from'?
	for (i = 0; i < length; i++) {
		for (j = i+1; j < length; j++) {
			if (from[i] == from[j]) {
				//print error
				fprintf(stderr, "Duplicate bytes found.");
				exit(1);
			}
		}
	}

	//transliterate bytes
	char s = getchar();
	while (s != EOF) {
		man = 0;
		for (i = 0; i < length; i++) {
			if (curr == from[i]) {
				putchar(to[i]);
				man = 1;
				break;
			}
		}
		//writes if man = 0
		if (man == 0) {
			putchar(curr);
		}
		//updates s
		s = getchar();
	}
	return 0;
}