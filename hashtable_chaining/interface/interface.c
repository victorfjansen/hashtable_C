#include "interface.h"

void interface_insert_key(hash_table *ht)
{
    char key_pair[MAX_NAME];
    char value_pair[MAX_NAME];

    puts("Write a key to associate to a value: \t");
    scanf("%s", key_pair);

    puts("Write a value: \t");
    scanf("%s", value_pair);

    dictionary *key_value_pair = NULL;
    key_value_pair = create_dictionary(key_pair, value_pair);
    hash_table_insert(ht, key_value_pair);
}

void interface_search_key(hash_table *ht)
{
    char to_search_key[MAX_NAME];

    puts("Write a key to search value: \t");
    scanf("%s", to_search_key);

    dictionary *foundValue = hash_table_lookup(ht, to_search_key);

    if (!foundValue)
    {
        puts("Any value was found");
        return;
    }

    printf("The found value for <%s> key was <%s> value", to_search_key, foundValue->value);
}

void interface_delete_key(hash_table *ht)
{
    char to_delete_key[MAX_NAME];

    puts("Write a key to delete: \t");
    scanf("%s", to_delete_key);

    int key_was_deleted = hash_table_delete(ht, to_delete_key);

    if (!key_was_deleted)
    {
        printf("Any key was deleted. Verify if key really exists in table");
        return;
    }

    printf("The key_value_pair was deleted for %s key", to_delete_key);
}

void interface_print_table(hash_table *ht)
{
    puts("\t Start of Table\t\n");
    print_table(ht);
    puts("\t End of Table\t\n");
}

void interface_destroy_table(hash_table *ht)
{
    puts("\tDestroying Table...< \t\n");
    destroy_hash_table(ht);
    puts("\tTable destroyed...< \t\n");

    puts("Your session was closed by table exclusion! Init the program again!");
    exit(EXIT_SUCCESS);
}

void interface_load_one_thousand__random_words(hash_table *ht)
{
    if (!load_json_into_hash_table(ht, "./database/palavras.json"))
    {
        fprintf(stderr, "Failed to load words database into hash_table.\n");
        destroy_hash_table(ht);
        exit(EXIT_FAILURE);
    }
}


void interface_print_initial_questions(int *selected_value)
{
    /**
     * Acertar isso
     */

    puts("\nWrite a number to init some operation:\n");
    puts("\t 1. Insert Key/Value: \t");
    puts("\t 2. Search Key: \t");
    puts("\t 3. Delete Key/Value: \t");
    puts("\t 4. Print Table: \t");
    puts("\t 5. Destroy Table: \t");
    puts("\t 6. Load 10.000 Words:\t");

    scanf("%d", selected_value);
}

void interface_dispatch_actions(int selected_value, hash_table *ht)
{
    switch (selected_value)
    {
    case 1:
        interface_insert_key(ht);
        break;
    case 2:
        interface_search_key(ht);
        break;
    case 3:
        interface_delete_key(ht);
        break;
    case 4:
        interface_print_table(ht);
        break;
    case 5:
        interface_destroy_table(ht);
        break;
    case 6:
        interface_load_one_thousand__random_words(ht);
        break;
    default:
        puts("deu ruim");
        break;
    }
}

void interface_init_program()
{
    hash_table *ht = NULL;
    ht = create_hash_table(TABLE_SIZE);

    while (1)
    {

        int selected_option = 0;
        interface_print_initial_questions(&selected_option);
        interface_dispatch_actions(selected_option, ht);
    }
}