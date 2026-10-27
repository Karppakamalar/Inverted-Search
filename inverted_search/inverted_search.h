#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 1
#define FAILURE 0

#define FILE_NOT_FOUND -1
#define FILE_EMPTY -2
#define FILE_REPEATED -3

#define SIZE 26
#define WORD_SIZE 30
#define FNAME_SIZE 30

typedef struct file_node
{
    char filename[FNAME_SIZE];
    struct file_node *link;
} File_node;


typedef struct sub_node
{
    int word_count;
    char filename[FNAME_SIZE];

    struct sub_node *link;

} sub_node_t;


typedef struct main_node
{
    int file_count;
    char word[WORD_SIZE];

    struct main_node *link;
    sub_node_t *sub_link;

} main_node_t;


// Validation functions //

int IsFileExist(char *filename);
int IsFileEmpty(char *filename);
int IsFileRepeated(char *filename, File_node *head);
int check_file(char *filename, File_node *head);

void insert_file(File_node **head, char *filename);
void display_files(File_node *head);

int create_database(File_node *file_head,main_node_t *hash_table[]);
int read_data_file(char *filename,main_node_t *hash_table[]);
int insert_main(char *word,char *filename,main_node_t **head);
int create_subnode(sub_node_t **subnode,char *filename);
int check_filename(main_node_t *main,char *filename);

int display_database(main_node_t *hash_table[]);

int search_database(main_node_t *hash_table[]);

int update_database(File_node **file_head,main_node_t *hash_table[]);

int save_database(main_node_t *hash_table[]);

#endif