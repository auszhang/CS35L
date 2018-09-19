#include<stdio.h>
#include<stdlib.h>


int frobcmp(char const *a, char const *b) {
	//returns in result that is negative, zero, or positive depending on whether a is less than, equal to, or greater than b
	while (1) {
		if (*a==' ')
			return 0;
		if (*a != *b)
			break;
		a++;
		b++;
	}
	return ((((*a)^42)<((*b)^42)?-1:1));
}

int comp(const void* one, const void* two) {
	//passes a1 and b2 into frobcmp
  	const char* a1=*(const char**)one;
  	const char* b2=*(const char**)two;
  	return frobcmp(a1,b2);
}

void error() {
	//as specified in the assignment...
	if(ferror(stdin)) {
		fprintf(stderr, "ERROR");
	  	exit(1);
	}
	else{
		exit(0);
	}
}

int main(void) {
	int ll=0;
  	int ww=0;

  	//array
  	char** a; 
  	a=(char**)malloc(sizeof(char*));

  	//string
  	char * s; 
  	s=(char*)malloc(sizeof(char));

  	char in=getchar();
  	error();
  	char l=getchar(); 
  	error();



  	while(l != EOF && !ferror(stdin)) {
  		s[ll]=l; 
  		char* temp=realloc(s, (ll+2)*sizeof(char));
  		if(temp != NULL) {
	 		s=temp;
		} else {
		  	free(s);
		  	
		  	fprintf(stderr, "Could not allocate memory");
		  	exit(1);
		}
		if(l == ' ') {
		  	a[ww]=s; 
		  	char** temp=realloc(a, (ww+2)*sizeof(char*));

		  	if(temp != NULL) {
		  		ll=-1;
				
				a=temp;
				ww++;
				
				s=NULL;
				s=(char*)malloc(sizeof(char));
				

		  	} else {
			  	free(a);
			  	
			  	fprintf(stderr, "Could not allocate memory"); //unable to allocate memory
			  	exit(1);
		  	}
		}

		if(in == EOF && l == ' ') {
		  	break;
		} else if (l == ' ' && in == ' ') {
		  	while(l == ' ') {
		  		l=getchar();
		  		error();
		  	}
		  	in=getchar();
		  	
		  	error();
		  	ll++;
		  	
		  	continue;
		} else if(in == EOF) {
		  
		  	l=' ';
		  	ll++;
		  	continue;
		}

		l=in;
		
		in=getchar();
		error();
		ll++;	
	}

  	qsort(a, ww, sizeof(char*), comp);

  	for(size_t i=0; i < ww; i++) {
  		
  		for(size_t j=0 ;; j++) {
			
			if(putchar(a[i][j]) == EOF) {
			  	fprintf(stderr, "Could not write character"); //unable to write character 
			  	exit(1);
			}
			
			if(a[i][j] == ' ') {
		  		break;
			}
		}
  	}

  	for(size_t i=0; i < ww; i++) {
  		free(a[i]);
  	}
  	
  	//free array and exit
  	free(a);
  	exit(0);
}