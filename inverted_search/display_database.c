#include "inverted_search.h"

int display_database(main_node_t *hash_table[])
{
    int i;

    for (i = 0; i < SIZE; i++)
    {
        main_node_t *main_temp = hash_table[i];

        if (main_temp == NULL)
        {
            continue;
        }

        while (main_temp != NULL)
        {
            printf("[%d]\t[%s]\t%d file(s) : ",i,main_temp->word,main_temp->file_count);

            sub_node_t *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                printf("file : %s : %d time(s) : ",sub_temp->filename,sub_temp->word_count);

                sub_temp = sub_temp->link;
            }

            printf("\n");

            main_temp = main_temp->link;
        }
    }

    return SUCCESS;
}