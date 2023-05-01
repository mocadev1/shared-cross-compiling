#ifndef copy_h__
#define copy_h__

#define BUFFER_SIZE 1024

int copy(int argc, char *argv[]);
void copy_file(char *source_path, char *destination_path);
void copy_directory(char *source_path, char *destination_path);

#endif