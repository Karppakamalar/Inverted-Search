#include "inverted_search.h"


void insert_file(File_node **head, char *filename)
{
    File_node *new = malloc(sizeof(File_node));

    if (new == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(new->filename, filename);

    new->link = NULL;

    if (*head == NULL)
    {
        *head = new;
        return;
    }

    File_node *temp = *head;

    while (temp->link != NULL)
    {
        temp = temp->link;
    }

    temp->link = new;
}


void display_files(File_node *head)
{
    File_node *temp = head;

    printf("\nFiles passed through command line:\n");

    while (temp != NULL)
    {
        printf("%s\n", temp->filename);

        temp = temp->link;
    }
}


int main(int argc, char *argv[])
{
    File_node *head = NULL;

    main_node_t *hash_table[SIZE];

    int i;
    int ret;
    int choice;

    for (i = 0; i < SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    if (argc == 1)
    {
        printf("ERROR: No files passed through command line\n");
        printf("Usage: ./a.out file1.txt file2.txt ...\n");

        return FAILURE;
    }

    for (i = 1; i < argc; i++)
    {
        ret = check_file(argv[i], head);

        if (ret == FILE_NOT_FOUND)
        {
            printf("ERROR: File %s not found\n", argv[i]);
            continue;
        }

        if (ret == FILE_EMPTY)
        {
            printf("ERROR: File %s is empty\n", argv[i]);
            continue;
        }

        if (ret == FILE_REPEATED)
        {
            printf("ERROR: File %s is repeated\n", argv[i]);
            continue;
        }

        insert_file(&head, argv[i]);

        printf("Successfully inserted file name : %s into file linked list\n",argv[i]);
    }


    display_files(head);

    do{
        printf("\n========== INVERTED SEARCH ==========\n");

        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice. Please enter a number from 1 to 6.\n");

            while (getchar() != '\n');

            continue;
        }

        switch (choice)
        {
            case 1:
                printf("\nCreating DATABASE...\n");

                create_database(head, hash_table);

                break;


            case 2:
                printf("\nDisplaying DATABASE\n");

                display_database(hash_table);

                break;


            case 3:
                printf("\nSearching DATABASE...\n");

                search_database(hash_table);

                break;


            case 4:
                printf("\nUpdating DATABASE...\n");

                update_database(&head, hash_table);

                break;


            case 5:
                printf("\nSaving DATABASE...\n");

                save_database(hash_table);

                break;


            case 6:
                printf("\nExiting\n");

                break;


            default:
                printf("\nInvalid choice. Please enter 1 to 6.\n");
        }

    }while(choice != 6);

return SUCCESS;
}