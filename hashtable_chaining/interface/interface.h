#include "../main.h"

#include "../hashtable/hashtable_chaining.h"

void interface_insert_key(hash_table *ht);

void interface_search_key(hash_table *ht);

void interface_delete_key(hash_table *ht);

void interface_print_table(hash_table *ht);

void interface_destroy_table(hash_table *ht);

void interface_load_one_thousand__random_words(hash_table *ht);

void interface_print_initial_questions(int *selected_value);

void interface_dispatch_actions(int selected_value, hash_table *ht);

void interface_init_program();
