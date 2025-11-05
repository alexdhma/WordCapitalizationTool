
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "traversal.h"
#include "report.h"

// ------ MAIN --------
int main(int argc, char *argv[]){

	// target word
	char *word = argv[1];
	
	// get current working directory
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));


	// search report
	printf("\nTarget string: %s\n", word);
	printf("Search begins in current folder: %s\n\n", cwd);
	printf("** Search Report **\n");
	printf("Updates\tFile Name\n");

	// search cwd for target word
	search_dir(cwd, word);

    sorted_updates();
	
	return EXIT_SUCCESS;	
}