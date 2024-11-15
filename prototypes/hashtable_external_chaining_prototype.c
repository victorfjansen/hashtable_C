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
    struct person *next;
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

        printf("\t%d\t", i);

        struct person *aux = hash_table[i];

        printf("AQUIII %p", hash_table);
        printf("AQUIII %p", hash_table[i]);
        while(aux != NULL) {
            printf("%s - ", aux->name);
            aux = aux->next;
        }

        printf("\n");
    }
}

int hash_table_insert(struct person *p)
{
    if (!p)
        return 0;
    int index = hash(p->name);

    p->next = hash_table[index];
    hash_table[index] = p;
    return 1;
}

struct person *create_person(char *name, int age)
{
    struct person *currPerson = (struct person *) malloc(sizeof(struct person));
    if (!currPerson) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    currPerson->age = age;
    strncpy(currPerson->name, name, MAX_NAME - 1);

    // SUGERIDO PELO CHAT - Faz Sentido?
    currPerson->name[MAX_NAME - 1] = '\0'; // Garantir terminação da string

    currPerson->next = NULL; 
    return currPerson;
}

struct person *hash_table_lookup(char *name)
{
    int index = hash(name);
    struct person *aux = hash_table[index];

    while (aux && strncmp(aux->name, name, MAX_NAME))
    {
        aux = aux->next;
    }

    return aux;
}

int hash_table_delete(char *name)
{
    int index = hash(name);
    struct person *aux = hash_table[index];
    struct person *prev = NULL;

    while (aux && strncmp(aux->name, name, MAX_NAME))
    {
        prev = aux;
        aux = aux->next;
    }

    if (!aux)
        return 0;

    if (!prev)
        hash_table[index] = aux->next;
    else
        prev->next = aux->next;

    free(aux);
    return 1;
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

    int hasDeleted = hash_table_delete("AP");

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
 * 
 * How to dimensionate the Table HashMap? Em que proporção eu posso assegurar minha memória e colocar um bom range para evitar colisões?
 * 
 * Em termos matemáticos, eu consigo calcular o quando um hashMap é eficiente pelo número de colisões e listas linkadas?
 * 
 * Existe alguma função de hash mais otimizada?
 * 
 * How precise should be my hash function?SS
 */