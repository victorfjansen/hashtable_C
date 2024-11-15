#include "json_loader.h"

// Função para ler todo o conteúdo de um arquivo em uma string
char* read_file(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char*) malloc(length + 1);
    if (!data) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);
    return data;
}

// Função para carregar o JSON na tabela hash
int load_json_into_hash_table(hash_table *ht, const char *filename) {
    if (!ht || !filename) return 0;

    char *json_data = read_file(filename);
    if (!json_data) return 0;

    cJSON *json = cJSON_Parse(json_data);
    if (!json) {
        fprintf(stderr, "Erro ao parsear JSON: %s\n", cJSON_GetErrorPtr());
        free(json_data);
        return 0;
    }

    cJSON *item = NULL;
    cJSON_ArrayForEach(item, json) {
        if (cJSON_IsString(item)) {
            const char *portuguese_word = item->string;
            const char *english_word = item->valuestring;

            if (portuguese_word && english_word) {
                dictionary *dict = create_dictionary((char*)portuguese_word, (char*)english_word);
                if (!hash_table_insert(ht, dict)) {
                    fprintf(stderr, "Falha ao inserir '%s' na tabela hash.\n", portuguese_word);
                }
            }
        }
    }

    cJSON_Delete(json);
    free(json_data);
    return 1;
}

char* translate_phrase(hash_table *ht, const char *portuguese_phrase) {
    if (!ht || !portuguese_phrase) {
        return NULL;
    }

    char *phrase_copy = strdup(portuguese_phrase);
    if (!phrase_copy) {
        perror("Erro ao alocar memória para a frase");
        return NULL;
    }

    size_t translated_size = strlen(portuguese_phrase) * 10 + 1; // Estimativa
    char *english_phrase = (char *) malloc(translated_size);
    if (!english_phrase) {
        perror("Erro ao alocar memória para a frase traduzida");
        free(phrase_copy);
        return NULL;
    }
    english_phrase[0] = '\0'; // Inicializa como string vazia

   const char *delimiters = " \t\n,.;:!?-()[]{}\"'";
   char *token = strtok(phrase_copy, delimiters);

   while (token != NULL) {
       // Remove possíveis pontuações no início e no fim da palavra
       char *clean_word = token;

       // Converte a palavra para minúsculas para correspondência
       for (int i = 0; clean_word[i]; i++) {
           if (clean_word[i] >= 'A' && clean_word[i] <= 'Z') {
               clean_word[i] += 'a' - 'A';
           }
       }

       // Busca a tradução na tabela hash
       dictionary *found = hash_table_lookup(ht, clean_word);
       if (found) {
           strcat(english_phrase, found->value);
       } else {
           strcat(english_phrase, "<NULL>");
       }

       strcat(english_phrase, " "); // Adiciona espaço após cada palavra
       token = strtok(NULL, delimiters);
   }

   // Remove o espaço extra no final
   size_t len = strlen(english_phrase);
   if (len > 0 && english_phrase[len - 1] == ' ') {
       english_phrase[len - 1] = '\0';
   }

   free(phrase_copy);
   return english_phrase;
}
