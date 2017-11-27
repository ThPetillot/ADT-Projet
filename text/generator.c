#include "generator.h"

void write_random_word(size_t wLen, size_t alphaLen, FILE * file);
char random_char(size_t alphabet_length);

int generate_text(size_t text_len, size_t alphabet_length, const char * file_path) {
    if (alphabet_length > ALPHABET_MAX_SIZE) {
        printf("(generate_text) failed : alphabet_length > ALPHABET_MAX_SIZE\n");
        return -1;
    }

    FILE * file = fopen(file_path, "w");

    if (file == NULL) {
        printf("(generate_text) failed : fopen return NULL\n");
        return -1;
    }

    write_random_word(text_len, alphabet_length, file);

    fclose(file);

    return 0;
}

int generate_words(size_t word_nb, size_t word_len, size_t alphabet_length, const char * file_path) {
    if (alphabet_length > ALPHABET_MAX_SIZE) {
        printf("(generate_words) failed : alphabet_length > ALPHABET_MAX_SIZE\n");
        return -1;
    }

    if (word_len > WORD_MAX_LEN) {
        printf("(generate_words) failed : world_len > WORD_MAX_LEN");
        return -1;
    }

    FILE * file = fopen(file_path, "w");

    if (file == NULL) {
        printf("(generate_words) failed : fopen return NULL\n");
        return -1;
    }

    char * eol = "\r\n";
    for (int i = 0; i < word_nb; i++) {
        write_random_word(word_len, alphabet_length, file);
        if (i < word_nb - 1) {
            fwrite(eol, sizeof(char), strlen(eol), file);
        }
    }

    fclose(file);
    return 0;
}

void write_random_word(size_t wLen, size_t alphaLen, FILE * file) {
    char buffer[FILE_CHUNK];
    int i = 0, flag = 0;
    while(i < wLen) {
        // Filling buffer with random char
        buffer[i%FILE_CHUNK] = random_char(alphaLen);
        i++;

        // Buffer full : write on file && reset buffer
        if (flag && i%FILE_CHUNK == 0) {
            fwrite(buffer, sizeof(char), FILE_CHUNK, file);
            memset(buffer, '\0', FILE_CHUNK);
        }

        // Flag for first iteration
        flag = 1;
    }

    if (i%FILE_CHUNK != 0) {
        fwrite(buffer, sizeof(char), i%FILE_CHUNK, file);
        memset(buffer, '\0', FILE_CHUNK);
    }
}

char random_char(size_t alphabet_length) {
    return (char) (ASCII_FIRST_CHAR + (rand()%alphabet_length));
}