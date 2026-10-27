#include "inverted_search.h"

int create_database(File_node *file_head,main_node_t *hash_table[])
{
    while (file_head != NULL)
    {
        read_data_file(file_head->filename, hash_table);

        file_head = file_head->link;
    }

    return SUCCESS;
}

int read_data_file(char *filename,main_node_t *hash_table[])
{
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("ERROR: Unable to open %s\n", filename);
        return FAILURE;
    }

    char word[WORD_SIZE];
    int index = 0;
    int ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalpha(ch))
        {
            if (index < WORD_SIZE - 1)
            {
                word[index++] = ch;
            }
        }
        else
        {
            if (index != 0)
            {
                word[index] = '\0';

                int hash_index;

                hash_index = tolower(word[0]) - 'a';

                if (hash_table[hash_index] == NULL)
                {
                    insert_main(word,filename,&hash_table[hash_index]);
                }
                else
                {
                    main_node_t *temp = hash_table[hash_index];

                    while (temp != NULL)
                    {
                        if (strcmp(temp->word, word) == 0)
                        {
                            check_filename(temp, filename);
                            break;
                        }

                        temp = temp->link;
                    }

                    if (temp == NULL)
                    {
                        insert_main(word,filename,&hash_table[hash_index]);
                    }
                }

                index = 0;
            }
        }
    }

    if (index != 0)
    {
        word[index] = '\0';

        int hash_index;

        hash_index = tolower(word[0]) - 'a';

        if (hash_table[hash_index] == NULL)
        {
            insert_main(word,
                        filename,
                        &hash_table[hash_index]);
        }
        else
        {
            main_node_t *temp = hash_table[hash_index];

            while (temp != NULL)
            {
                if (strcmp(temp->word, word) == 0)
                {
                    check_filename(temp, filename);
                    break;
                }

                temp = temp->link;
            }

            if (temp == NULL)
            {
                insert_main(word,filename,&hash_table[hash_index]);
            }
        }
    }

    fclose(fp);
    printf("Successfully read file %s\n", filename);

    return SUCCESS;
}

int insert_main(char *word,char *filename,main_node_t **head)
{
    main_node_t *new = malloc(sizeof(main_node_t));

    if (new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->word, word);

    new->file_count = 1;
    new->link = NULL;
    new->sub_link = NULL;

    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        main_node_t *temp = *head;

        while (temp->link != NULL)
        {
            temp = temp->link;
        }

        temp->link = new;
    }

    create_subnode(&new->sub_link, filename);

    return SUCCESS;
}

int create_subnode(sub_node_t **subnode,char *filename)
{
    sub_node_t *new = malloc(sizeof(sub_node_t));

    if (new == NULL)
    {
        return FAILURE;
    }

    new->word_count = 1;

    strcpy(new->filename, filename);

    new->link = NULL;

    if (*subnode == NULL)
    {
        *subnode = new;
        return SUCCESS;
    }

    sub_node_t *temp = *subnode;

    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;

    return SUCCESS;
}

int check_filename(main_node_t *main,char *filename)
{
    sub_node_t *temp = main->sub_link;

    while (temp != NULL)
    {
        if (strcmp(temp->filename, filename) == 0)
        {
            temp->word_count++;

            return SUCCESS;
        }

        temp = temp->link;
    }

    create_subnode(&main->sub_link, filename);

    main->file_count++;

    return SUCCESS;
}