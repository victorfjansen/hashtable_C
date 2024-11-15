#include "main.h"

// gcc -o my_program main.c hashtable/hashtable_external_chaining.c json_loader/json_loader.c cJSON/cJSON.c interface/interface.c -lcjson

int main()
{
   interface_init_program();

    // Carregar o arquivo JSON na tabela hash - GTP
    // if (!load_json_into_hash_table(ht, "./database/palavras.json"))
    // {
    //     fprintf(stderr, "Falha ao carregar o arquivo JSON na tabela hash.\n");
    //     destroy_hash_table(ht);
    //     return EXIT_FAILURE;
    // }

    // print_table(ht);

    // struct dictionary *eu = create_dictionary("eu", "i");
    // struct dictionary *gosto = create_dictionary("gosto", "like");
    // struct dictionary *de = create_dictionary("de", "of");
    // struct dictionary *caminhar = create_dictionary("caminhar", "walk");

    // hash_table_insert(ht, eu);
    // hash_table_insert(ht, gosto);
    // hash_table_insert(ht, de);
    // hash_table_insert(ht, caminhar);

    // const char *portuguese_sentence = "eu gosto de caminhar";
    // char *english_translation = translate_phrase(ht, portuguese_sentence);
    // if (english_translation)
    // {
    //     printf("Frase em Português: %s\n", portuguese_sentence);
    //     printf("Frase em Inglês: %s\n", english_translation);
    //     free(english_translation);
    // }
    // else
    // {
    //     printf("Falha na tradução da frase.\n");
    // }

    // Adicionar Testes de performance 

    // struct dictionary *today = create_dictionary("hoje", "today");
    // struct dictionary *tomorrow = create_dictionary("amanhã", "tomorrow");
    // struct dictionary *im = create_dictionary( "eu", "im");

    // // colisão forçada
    //     struct dictionary *forced_colision1 = create_dictionary( "olá", "hello");
    // struct dictionary *forced_colision2 = create_dictionary( "como", "how");

    // // Declaração simples
    // hash_table_insert(ht, im);
    // hash_table_insert(ht, today);
    // hash_table_insert(ht, tomorrow);

    // // Declaração com o mesmo hash - Colisão
    // hash_table_insert(ht, forced_colision1);
    // hash_table_insert(ht, forced_colision2);

    // print_table(ht);

    // printf("Found dictionary, %s\n", hash_table_lookup(ht,today->key)->value);

    // int hasDeleted = hash_table_delete(ht, today->key);

    // if (hasDeleted)
    //     puts("Deletou");
    // else
    //     puts("Não deletou");

    // print_table(ht);

    return 0;
}
