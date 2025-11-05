#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "traversal.h"
#include "text.h"

// search_dir function
void search_dir(const char *dir_name, const char *target){

	// open directory
	DIR *dp = opendir(dir_name);
	if(!dp) {
		perror("Error opening directory!");
		return;
	}

	// get file/directory info
	struct dirent *dirp;
	struct stat statbuf;
	// string to store its path
	char path[1024];


	// loop for every entry in a directory
	while (((dirp = readdir(dp)) != NULL)) {

		// skip current folder and parent folder
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		// path of file/folder
		snprintf(path, sizeof(path), "%s/%s", dir_name, dirp->d_name);
		if (lstat(path, &statbuf)<0) {
			perror("Error getting file info!");
			continue;
		}

		// check if its a directory
		if (S_ISDIR(statbuf.st_mode)) {
			search_dir(path, target);

			// check if its a file and its .txt
		} else if (S_ISREG(statbuf.st_mode)){
			if (strstr(dirp->d_name, ".txt") != NULL) {
				process_file(path, target);
			}
		}
	}
    closedir(dp);
}


