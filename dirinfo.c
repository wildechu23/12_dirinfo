#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[]) {


    DIR *dir;
    char *path;
    if(argc == 2) path = argv[1];
    if((dir = opendir(path)) == NULL) {
        printf("Error: %s\n", strerror(errno));
        return 0;
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