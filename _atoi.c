#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

// Function to list directory contents
int my_ls(char *path) {
    DIR *dir;
    struct dirent *ent;
    struct stat statbuf;

    // Change directory (handle errors)
    if (chdir(path) != 0) {
        perror("chdir");
        return EXIT_FAILURE;
    }

    // Open directory (handle errors)
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // Read directory entries and print file names
    while ((ent = readdir(dir)) != NULL) {
        // Get file attributes (handle errors)
        if (stat(ent->d_name, &statbuf) != 0) {
            perror("stat");
            continue;
        }

        // Check if regular file and print name
        if (S_ISREG(statbuf.st_mode)) {
            printf("%s\n", ent->d_name);
        }
    }

    // Close directory and change back
    closedir(dir);
    chdir("..");

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    // Handle options and call my_ls
    if (argc > 2) {
        fprintf(stderr, "usage: %s [directory]\n", argv[0]);
        return EXIT_FAILURE;
    }

    return my_ls(argc == 2 ? argv[1] : ".");
}

