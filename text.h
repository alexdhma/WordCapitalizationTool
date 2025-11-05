#ifndef TEXT_H
#define TEXT_H

void process_file(const char *file_name, const char *target);
char *read_file(const char *file_name, long *file_size);
int to_uppercase(char *buffer, const char *word);
void write_file(const char *file_name, const char *buffer);

#endif