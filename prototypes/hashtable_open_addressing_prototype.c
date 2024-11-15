#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

struct person
{
    char name[MAX_NAME];
    int age;
    // other stuff
};

struct person *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    // pega o tamanho do nome
    int length = strlen(name);

    // cria uma variável de hash
    unsigned int hash_value = 0;

    // para cada letra no nome
    for (int i = 0; i < length; i++)
    {
        // adiciona a hash_value o caracter na posição - como estamos tratando de unsigned int, pegamos o valor ascii
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table()
{
    // tabela vazia
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
}

void print_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        struct person *selected_person = hash_table[i];

        if (!selected_person)
        {
            printf("\t%d\t---\n", i);
            continue;
        }

        printf("\t%d\t%s\n", i, hash_table[i]->name);
    }
}

int hash_table_insert(struct person *p)
{
    if (!p)
        return 0;
    int index = hash(p->name);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try_index = (i + index) % TABLE_SIZE;

        if (!hash_table[try_index])
        {
            hash_table[try_index] = p;
            return 1;
        }
    }

    return 0;
}

struct person *create_person(char *name, int age)
{
    struct person *currPerson = NULL;

    currPerson = malloc(sizeof(struct person));
    currPerson->age = age;
    strcpy(currPerson->name, name);

    return currPerson;
}

struct person *hash_table_lookup(char *name)
{
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try_index = (index + i) % TABLE_SIZE;
        struct person *foundPerson = hash_table[try_index];
        if (foundPerson && !strncmp(foundPerson->name, name, MAX_NAME))
            return foundPerson;
    }

    return NULL;
}

// Cenário esquisito - Perguntar ao Alan
// int hash_table_delete(char *name) {
//     struct person *foundPerson = hash_table_lookup(name);

//     if(foundPerson) {
//             struct person *aux = foundPerson;
//             free(aux);

//             foundPerson = NULL;
//             return 1;
//     }
//     return 0;
// }

// Deu certo chamando a referência direta - SEM COLISÃO
// int hash_table_delete(char *name)
// {
//     int index = hash(name);
//     struct person *foundPerson = hash_table[index];

//     if (foundPerson && !strncmp(foundPerson->name, name, TABLE_SIZE))
//     {
//         free(hash_table[index]);
//         hash_table[index] = NULL;
//         return 1;
//     }

//     return 0;
// }

int hash_table_delete(char *name)
{
    int index = hash(name);

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try_index = (index + i) % TABLE_SIZE;
        struct person *foundPerson = hash_table[try_index];
        if (foundPerson && !strncmp(foundPerson->name, name, MAX_NAME)) {
            free(foundPerson);
            hash_table[try_index] = NULL;
            return 1;
        }
           
    }

    return 0;
}

int main()
{

    init_hash_table();

    struct person *victor = create_person("victor", 19);
    struct person *alan = create_person("Alan", 30);
    struct person *sulamita = create_person("Sulamita", 21);

    // colisão forçada
    struct person *forced_colision1 = create_person("AP", 21);
    struct person *forced_colision2 = create_person("AF", 21);

    // Declaração simples
    hash_table_insert(victor);
    hash_table_insert(alan);

    // Declaração com o mesmo hash - Colisão
    hash_table_insert(sulamita);
    hash_table_insert(forced_colision1);
    hash_table_insert(forced_colision2);

    print_table();

    printf("Found person, %s\n", hash_table_lookup(victor->name)->name);

    int hasDeleted = hash_table_delete("AF");

    if (hasDeleted)
        puts("Deletou");
    else
        puts("Não deletou");

    print_table();

    // printf("Victor => %u\n", hash("Victor"));
    // printf("Sulamita => %u\n", hash("Sulamita"));
    // printf("Alan => %u\n", hash("Alan"));
    // printf("Emanuel => %u\n", hash("Emanuel"));
    // printf("Damaso => %u\n", hash("Damaso"));

    return 0;
}

// Notes
/**
 * When colliding, we can use 2 approaches:
 * - Open Addressing
 * - External Chaining
 *
 *
 * If occurs the colision, the open addressing strategy gets the next memory address and looks if its full.
 * If yes, they go to the next node and allocate on there. (This approach can lead us to travel the entire list).
 *
 * Discuss this point with Allan.!!!!!
 */