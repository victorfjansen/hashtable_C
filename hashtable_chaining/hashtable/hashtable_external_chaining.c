#include "hashtable_chaining.h"

unsigned int hash(char *name, size_t table_size)
{
    // cria uma variável de hash
    unsigned int hash_value = 0;

    // para cada letra no nome
    for (int i = 0; name[i] != '\0'; i++)
    {
        // adiciona a hash_value o caracter na posição - como estamos tratando de unsigned int, pegamos o valor ascii
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % table_size;
    }
    return hash_value;
}

hash_table* create_hash_table(size_t size) {
    hash_table *ht = NULL;
    ht = (hash_table *) malloc(sizeof(hash_table));

    if(!ht) {
        puts("Failed to allocate memory for hash table");
        exit(EXIT_FAILURE);
    }

    ht->size = size;
    ht->table = malloc(sizeof(dictionary *) * size);

    if(!(ht->table)) {
        puts("Failed to allocate memory for hashtable items");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }

    return ht;
}

int hash_table_insert(hash_table *ht, dictionary *dict)
{
    if (!dict || !ht)
        return 0;

    unsigned int index = hash(dict->key, ht->size);

    dict->next = ht->table[index];
    ht->table[index] = dict;
    return 1;
}

// Verificar se funciona
dictionary *hash_table_lookup(hash_table * ht,  char *key)
{
    if(!ht) return NULL;

    int index = hash(key, ht->size);

    dictionary *aux = ht->table[index];

    while (aux && strncmp(aux->key, key, MAX_NAME))
    {
        aux = aux->next;
    }

    return aux;
}

int hash_table_delete(hash_table *ht,char *key)
{

    if(!ht) return 0;

    int index = hash(key, ht->size);

    dictionary *aux = ht->table[index];
    dictionary *prev = NULL;

    while (aux && strncmp(aux->key, key, MAX_NAME))
    {
        prev = aux;
        aux = aux->next;
    }

    // Caso 1: No nao foi encontrado
    if (!aux)
        return 0;

    // Caso 2:  Nao ha no anterior e ha no no next
    if (!prev)
        ht->table[index] = aux->next;
    else
        prev->next = aux->next;

    free(aux);
    return 1;
}

void print_table(hash_table * ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        dictionary *selected_dictionary = ht->table[i];

        if (!selected_dictionary)
        {
            printf("\t%d\t---\n", i);
            continue;
        }

        printf("\t%d\t", i);
        while(selected_dictionary != NULL) {
            printf("%s - ", selected_dictionary->value);
            selected_dictionary = selected_dictionary->next;
        }

        printf("\n");
    }
}


dictionary *create_dictionary(char *key, char *value)
{
    dictionary *current_dictionary = (dictionary *) malloc(sizeof(dictionary));
    if (!current_dictionary) {
        puts("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    strncpy(current_dictionary->value, value, MAX_NAME - 1);
    strncpy(current_dictionary->key, key, MAX_NAME - 1);

    current_dictionary->value[MAX_NAME - 1] = '\0'; // Garantir terminação da string
    current_dictionary->key[MAX_NAME - 1] = '\0'; // Garantir terminação da string

    current_dictionary->next = NULL; 
    return current_dictionary;
}

void destroy_hash_table(hash_table *ht) {
    if(!ht) return;

    for(int i = 0; i < ht->size; i++) {
        dictionary *selected_dictionary = ht->table[i];

        while(selected_dictionary) {
            dictionary *tmp = selected_dictionary;
            selected_dictionary = selected_dictionary->next;
            free(tmp);
        }
    }

    free(ht->table);
    free(ht);
}
