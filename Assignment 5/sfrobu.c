//NOTE: review later
/*
* Austin Zhang
* 604736503
* CS35L
* sfrobu.c
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int flag;

//added get_buffer function
size_t get_buffer(char** frob_words, char* buffer, size_t size) {
 	//get buffer
    size_t line_num;
    size_t i;
    char* line = buffer;
    for (line_num = 0, i = 0; i < size; i++) {
        if (buffer[i] == ' ') {
            frob_words[line_num++] = line;
            line = buffer + i + 1;
        }
    }
    return line_num;
}

//from previous sfrob.c
int frobcmp(char const* a, char const* b) {
	//returns in result that is negative, zero, or positive depending on whether a is less than, equal to, or greater than b
    while (1) {
		if (*a==' ')
			return 0;
		if (*a != *b)
			break;
		a++;
		b++;
    }

    if (!flag) {
        //NOTE: check later?
        return ( ( ((*a)^42) < ((*b)^42) ? -1:1) );
    }
    else {
        //NOTE: check later?
        return ( ( toupper((*a)^42) < toupper((*b)^42) ? -1:1) );
    }
}

//from previous sfrob.c
int compare_pointers(const void *one, const void *two) {
    //passes a1 and b2 into frobcmp
  	const char* a1=*(const char**)one;
  	const char* b2=*(const char**)two;
  	return frobcmp(a1,b2);
}

//changed main
int main(int argc, char *argv[]) {
    int (* cmp) (const void*, const void*);
    
    ssize_t val;

    size_t line_num;
    size_t line_size;
    size_t file_size;
    size_t buffer_size;
    size_t i;

    int c;
    int done; 
    int space;

    char current_char;
    char reader[2];

    char* next;
    char* temp;
    char* line;

    char** frob_words;

    struct stat bufp;

    line_num = 0;
    line_size = 0;
    buffer_size = 0;
    done = 0;

    val = fstat(STDIN_FILENO, &bufp);
    
    if (val < 0) {
        fprintf(stderr, "%s Error\n", "IO");
        exit(1);
    }

    //set flag
    while (( c = getopt(argc, argv, "f")) != -1) {
        if (c == 'f') {
            flag = 1;
        }
    }

    cmp = &compare_pointers;
    
    //NOTE: change later?
    file_size = bufp.st_size + 1;
    next = (char*) malloc(sizeof(char) * file_size);
    line = next;
    
    while (done == 0) {
        //checks for IO error
        val = read(STDIN_FILENO, reader, 1);
        if (val < 0) {
            fprintf(stderr, "%s Error\n", "IO");
            exit(1);            
        }

        //no IO error
        current_char = reader[0];
        space = current_char == ' ';
        done = !val;

        if (file_size == buffer_size) {
            //move
            file_size *= 2;
            temp = (char*) realloc(next, sizeof(char) * file_size);
            next = temp;
        }
        
        if (!done) {
            next[buffer_size++] = current_char;
            line_size++;
        }
        else {
            //free next if empty buffer
            if (buffer_size == 0) {
                free(next);
                return 0;        
            }
            if (next[buffer_size - 1] != ' ') {
                next[buffer_size++] = ' ';
            }
            if (!line_size) {
                break;
            }
        }
        line_size = 0;
        line_num++;
    }
    frob_words = (char**) malloc(sizeof(char*) * line_num);
    
    //checks for correct line
    if (line_num != get_buffer(frob_words, next, buffer_size)) {
        //NOTE: do later?
        fprintf(stderr, "%s Error\n", "Incorrect line");
        exit(1);
    }
    
    // sort frob words from buffer
    qsort(frob_words, line_num, sizeof(char*), cmp);
    
    for (i = 0; i < line_num; i++) {
        ssize_t val;
        const char* word = frob_words[i];
        while (1) {
            //write value
            val = write(STDOUT_FILENO, word, 1);
            //check IO
            if (val < 0) {
                fprintf(stderr, "%s Error\n", "IO");
                exit(1);
            }
            if (*word++ == ' ') {
                break;
            }
        }
    }
    
    //free memory and return
    free(frob_words);
    free(next);
    return 0;
}