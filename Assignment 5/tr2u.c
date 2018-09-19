/*
 * Austin Zhang
 * 604736503
 * CS35L
 * tr2u.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
	int man;

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
	for (i = 0; i <= length-1; i++) {
		for (j = i+1; j <= length-1; j++) {
			if (from[j] == from[i]) {
				//print error
				fprintf(stderr, "Duplicate bytes found.");
				exit(1);
			}
		}
	}

	//transliterate bytes
	ssize_t s = read(0, array, 1);
	while (s >= 1) {
		man = 0;

		//from->to
		for (i=0; i < length; i++) {
			if (array[0] = from[i]) {
				array[0] = to[i];
				man = 1;
				write(1, array, 1);
				break;
			}
		}
		//writes if man = 0
		if (man == 0) {
			write(1, array, 1);
		}
		//update s
		s = read(0, array, 1);
	}
	return(0);
}