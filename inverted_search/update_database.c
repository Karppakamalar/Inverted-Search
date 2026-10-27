#include "inverted_search.h"

int update_database(File_node **file_head,main_node_t *hash_table[])
{
    char filename[FNAME_SIZE];

    printf("\nEnter the filename to update: ");
    scanf("%s", filename);

    if (IsFileExist(filename) == FILE_NOT_FOUND)
    {
        printf("ERROR: File %s not found\n", filename);
        return FAILURE;
    }

    if (IsFileEmpty(filename) == FILE_EMPTY)
    {
        printf("ERROR: File %s is empty\n", filename);
        return FAILURE;
    }

    if (IsFileRepeated(filename, *file_head) == FILE_REPEATED)
    {
        printf("ERROR: File %s is already present\n", filename);
        return FAILURE;
    }

    read_data_file(filename, hash_table);
    insert_file(file_head, filename);

    printf("Database updated successfully for file  %s\n", filename);

    return SUCCESS;
}