#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


int main() {
    DIR *dir;
    char *path = "./";
    dir = opendir(path);
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