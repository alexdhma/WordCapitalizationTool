#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

// initialize update_count
file_update updates[100];
int update_count = 0;

// add_update function
void add_update(const char *file_name, int count)
{

    // write back to file if target word was found and replaced
    if (count > 0) {

        // duplicate file path in memory and the number of updates
        updates[update_count].file_name = strdup(file_name);
        updates[update_count].count = count;
        update_count++;
    }
}

// compare_updates function
int compare_updates(const void *a, const void *b) {

	// number of update in each file
	file_update *fa = (file_update *)a;
	file_update *fb = (file_update *)b;

	// return the one with more updates
	return fb-> count-fa ->count;
}

// sort by number of updates
void sorted_updates() {
	qsort(updates, update_count, sizeof(file_update), compare_updates);
	for (int i=0; i< update_count; i++) {
		printf("%d\t %s\n", updates[i].count, updates[i].file_name);
		free(updates[i].file_name);
	}
}