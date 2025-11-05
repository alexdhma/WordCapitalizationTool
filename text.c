#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "text.h"
#include "report.h"

// read_file function
char *read_file(const char *file_name, long *file_size) {
	// file_pointer points to open file_name and read only "r"
	FILE *file_pointer = fopen(file_name, "r");
	if (!file_pointer) {
		perror("Error opening file!");
		return NULL;
	}

	// get file size
	// moves file_pointer to the end of the file
	fseek(file_pointer, 0, SEEK_END);
	// ftell returns position of file_pointer
	*file_size = ftell(file_pointer);
	// moves file_pointer back to beginning
	rewind(file_pointer);

	// place file into string buffer
	// buffer pointer points to first memory allocation of size file_size+1
	char *buffer = (char *)malloc(*file_size + 1);
	if (!buffer) {
		perror("Error in memory allocation!");
		return NULL;
	}

	// read entire file into buffer
	fread(buffer, 1, *file_size, file_pointer);
	// end buffer w/ null character '\0' at the end 
	buffer[*file_size] = '\0';

	// close current file and return buffer
	fclose(file_pointer);
	return buffer;
}

// to_uppercase function
int to_uppercase(char *buffer, const char *word){
	int count = 0;
	// number of character in target word
	int word_length = strlen(word);
	// for all characters in buffer
	for (int i=0; buffer[i]!='\0'; i++){
		// find target word
		if (strncasecmp(&buffer[i], word, word_length)==0){
			// change matching word to uppercase
			for (int j =0; j<word_length; j++){
				buffer[i+j] = toupper(buffer[i+j]);
			}
			count++;
		}
	}
	return count;
}

// write_file function
void write_file(const char *file_name, const char *buffer){
	// open file and write
	FILE *file_pointer = fopen(file_name, "w");
	if (!file_pointer){
		perror("Error opening file to write back!");
		return;
	}
	// write content of buffer back to file
	fputs(buffer, file_pointer);

	// close file
	fclose(file_pointer);
}

// process_file function
void process_file(const char *file_name, const char *target) {
	long file_size;
	char *content = read_file(file_name, &file_size);

	// change target word to uppercase
	if (content != NULL) {
		int count = to_uppercase(content, target);

		// write back to file if target word was found and replaced
		if (count >0) 
			write_file(file_name, content);

        add_update(file_name, count);

		// free memory content
		free(content);
	}
}
		
