#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    DIR *dir;
    char path[100];
    if((argc == 2) && (dir = opendir(argv[1])) == NULL) {
        printf("Error: %s\n", strerror(errno));
    }
    while(dir == NULL) {
        printf("Please enter a proper path:\n");
        int bytes_read = read(STDIN_FILENO, path, 100);
        if(path[bytes_read - 1] == '\n') path[bytes_read - 1] = '\0';
        dir = opendir(path);
	if(dir == NULL) printf("Error: %s\n", strerror(errno));
    }
    struct dirent *entry;

    printf("Statistics of directory: %s\n", path);
    printf("Directories:\n");
    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_DIR) {
            printf("%s\n", entry->d_name);
        }
    }
    rewinddir(dir);

    int byte_sum = 0;
    struct stat *buffer;
    buffer = malloc(sizeof(struct stat));
    printf("Regular Files:\n");
    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
            stat(entry->d_name, buffer);
            byte_sum += buffer->st_size;
        }
    }
    printf("Total size: %d bytes\n", byte_sum);
    free(buffer);
    return 0;
}
