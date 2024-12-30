#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdint.h>


typedef struct File {
    char *name;          // Nome do arquivo
    struct File *next; 
    struct File *prev;   
} File;


typedef struct Directory {
    char *name;            // Nome do diretório
    struct Directory *next;
    struct Directory *prev; 
    File *file;
    struct Directory *sub_dir; // Subdiretórios
} Directory;

Directory *create_directory(char *name);
File *create_file(char *name);
void add_file_to_directory(Directory *dir, File *file);
void list_files(Directory *dir);

#endif
