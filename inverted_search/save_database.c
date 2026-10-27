#include "inverted_search.h"

int save_database(main_node_t *hash_table[])
{
    char filename[FNAME_SIZE];

    printf("\nEnter the database filename to save: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("ERROR: Unable to open database file\n");
        return FAILURE;
    }

    int i;

    for (i = 0; i < SIZE; i++)
    {
        main_node_t *main_temp = hash_table[i];

        while (main_temp != NULL)
        {
            fprintf(fp, "#%d;%s;%d;",i,main_temp->word,main_temp->file_count);

            sub_node_t *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                fprintf(fp, "%s;%d;",sub_temp->filename,sub_temp->word_count);

                sub_temp = sub_temp->link;
            }

            fprintf(fp, "#\n");

            main_temp = main_temp->link;
        }
    }

    fclose(fp);

    printf("Database saved successfully to: %s\n", filename);

    return SUCCESS;
}