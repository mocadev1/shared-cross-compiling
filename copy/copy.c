#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void copy_file(char *source_path, char *destination_path) {
    // Open the source file for reading
    int source_fd = open(source_path, O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        exit(1);
    }

    // Get the size of the source file
    struct stat source_stat;
    if (fstat(source_fd, &source_stat) < 0) {
        perror("Error getting source file size");
        close(source_fd);
        exit(1);
    }

    // Open the destination file for writing
    int destination_fd = open(destination_path, O_CREAT | O_WRONLY | O_TRUNC, source_stat.st_mode);
    if (destination_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);
        exit(1);
    }

    // Copy the contents of the source file to the destination file
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(destination_fd, buffer, bytes_read);
        if (bytes_written < 0) {
            perror("Error writing to destination file");
            close(source_fd);
            close(destination_fd);
            exit(1);
        }
    }

    // Check for errors during copying
    if (bytes_read < 0) {
        perror("Error reading from source file");
        close(source_fd);
        close(destination_fd);
        exit(1);
    }

    // Close the file descriptors
    close(source_fd);
    close(destination_fd);
}

void copy_directory(char *source_path, char *destination_path) {
    // Create the destination directory if it doesn't exist
    if (mkdir(destination_path, 0777) < 0) {
        perror("Error creating destination directory");
        exit(1);
    }

    // Open the source directory
    DIR *source_dir = opendir(source_path);
    if (!source_dir) {
        perror("Error opening source directory");
        exit(1);
    }

    // Loop through the source directory entries
    struct dirent *entry;
    while ((entry = readdir(source_dir))) {
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path of the source file/directory
        char *source_entry_path = malloc(strlen(source_path) + strlen(entry->d_name) + 2);
        sprintf(source_entry_path, "%s/%s", source_path, entry->d_name);

        // Construct the full path of the destination file/directory
        char *destination_entry_path = malloc(strlen(destination_path) + strlen(entry->d_name) + 2);
        sprintf(destination_entry_path, "%s/%s", destination_path, entry->d_name);

        // Copy the file/directory recursively
        struct stat source_entry_stat;
        if (lstat(source_entry_path, &source_entry_stat) < 0) {
            perror("Error getting source entry status");
            free(source_entry_path);
            free(destination_entry_path);
            closedir(source_dir);
            exit(1);
        }
       
        // If the entry is a directory, copy it recursively
        if (S_ISDIR(source_entry_stat.st_mode)) {
        copy_directory(source_entry_path, destination_entry_path);
        }
        // Otherwise, copy the file
        else {
        copy_file(source_entry_path, destination_entry_path);
        }

        // Free the entry paths
            free(source_entry_path);
            free(destination_entry_path);
    }

    // Check for errors during directory copying
    if (errno) {
        perror("Error copying directory");
        closedir(source_dir);
        exit(1);
    }

    // Close the source directory
    closedir(source_dir);

}

int main(void) {
    int recursive = 0;
    char source_path[100];
    char destination_path[100];

    printf("Enter the source path: ");
    if (fgets(source_path, 100, stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read source path\n");
        exit(1);
    }
    source_path[strcspn(source_path, "\n")] = 0;

    printf("Enter the destination path: ");
    if (fgets(destination_path, 100, stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read destination path\n");
        exit(1);
    }
    destination_path[strcspn(destination_path, "\n")] = 0;

    printf("Do you want to copy recursively? (y/n) ");
    char answer[2];
    if (fgets(answer, 2, stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read answer\n");
        exit(1);
    }

    if (strcmp(answer, "y") == 0) {
        recursive = 1;
    }

    if (recursive) {
        copy_directory(source_path, destination_path);
    } else {
        copy_file(source_path, destination_path);
    }

    return 0;
}