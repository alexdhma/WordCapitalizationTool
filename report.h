#ifndef REPORT_H
#define REPORT_H

// struct for number of updates
typedef struct {
	char *file_name;
	int count;
} 
file_update;

// declare
extern file_update updates[100];
extern int update_count;

void add_update(const char *file_name, int count);
int compare_updates(const void *a, const void *b);
void sorted_updates();

#endif