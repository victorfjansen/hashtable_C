#include "../main.h"


typedef struct dictionary {
    char key[MAX_NAME];
    char value[MAX_NAME];
    struct dictionary *next;
} dictionary;

typedef struct hash_table {
    size_t size;
    dictionary **table;
} hash_table;


unsigned int hash(char *name, size_t table_size);

hash_table* create_hash_table(size_t size);

int hash_table_insert(hash_table *ht, dictionary *dictionary);

dictionary *hash_table_lookup(hash_table *ht, char *key);

int hash_table_delete(hash_table *ht, char *key);

void print_table(hash_table *ht);

dictionary *create_dictionary(char *key, char *value);

void destroy_hash_table(hash_table *ht);

