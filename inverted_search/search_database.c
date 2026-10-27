#include "inverted_search.h"

int search_database(main_node_t *hash_table[])
{
    char word[WORD_SIZE];

    printf("\nEnter the word to search: ");
    scanf("%s", word);

    int index;

    index = tolower(word[0]) - 'a';

    main_node_t *temp = hash_table[index];

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            printf("\nWord \"%s\" is found in the database\n", word);
            printf("It is present in %d file(s)\n",temp->file_count);

            sub_node_t *sub_temp = temp->sub_link;

            while (sub_temp != NULL)
            {
                printf("In file %s : %d time(s)\n",sub_temp->filename,sub_temp->word_count);

                sub_temp = sub_temp->link;
            }

            return SUCCESS;
        }

        temp = temp->link;
    }

    printf("\nWord \"%s\" is not found in the database\n", word);

    return FAILURE;
}