#ifndef VALIDATION_H
#define VALIDATION_H

#include "inverted_search.h"

int IsFileExist(char *filename);
int IsFileEmpty(char *filename);
int IsFileRepeated(char *filename, File_node *head);
int check_file(char *filename, File_node *head);

#endif