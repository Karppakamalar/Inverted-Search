#include "validation.h"

int IsFileExist(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        return FILE_NOT_FOUND;
    }

    fclose(fp);

    return SUCCESS;
}

int IsFileEmpty(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        return FILE_NOT_FOUND;
    }

    fseek(fp, 0, SEEK_END);

    long size = ftell(fp);

    fclose(fp);

    if (size == 0)
    {
        return FILE_EMPTY;
    }

    return SUCCESS;
}


int IsFileRepeated(char *filename, File_node *head)
{
    File_node *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            return FILE_REPEATED;
        }

        temp = temp->link;
    }

    return SUCCESS;
}

int check_file(char *filename, File_node *head)
{
    int ret;
    ret = IsFileExist(filename);

    if (ret == FILE_NOT_FOUND)
    {
        return FILE_NOT_FOUND;
    }

    ret = IsFileEmpty(filename);

    if (ret == FILE_EMPTY)
    {
        return FILE_EMPTY;
    }


    ret = IsFileRepeated(filename, head);

    if (ret == FILE_REPEATED)
    {
        return FILE_REPEATED;
    }

    return SUCCESS;
}