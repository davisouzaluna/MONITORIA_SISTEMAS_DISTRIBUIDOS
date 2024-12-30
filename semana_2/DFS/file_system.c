#include "file_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Directory *create_directory(char *name) {
    Directory *dir = (Directory *)malloc(sizeof(Directory));
    dir->name = strdup(name);
    dir->next = NULL;
    dir->prev = NULL;
    dir->file = NULL;
    dir->sub_dir = NULL;
    return dir;
}

File *create_file(char *name) {
    File *file = (File *)malloc(sizeof(File));
    file->name = strdup(name);
    file->next = NULL;
    file->prev = NULL;
    return file;
}
void add_file_to_directory(Directory *dir, File *file) {
    if (dir->file == NULL) {
        dir->file = file;
    } else {
        File *aux = dir->file;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = file;
        file->prev = aux;
    }
}

void list_files(Directory *dir) {
    printf("Files in directory '%s':\n", dir->name);
    File *file = dir->file;
    while (file != NULL) {
        printf(" - %s\n", file->name);
        file = file->next;
    }
}
