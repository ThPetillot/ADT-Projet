#ifndef ADT_TP1_GENERATOR_H
#define ADT_TP1_GENERATOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const char ASCII_FIRST_CHAR = '0';
static const char ASCII_LAST_CHAR = 'z';
static const size_t ALPHABET_MAX_SIZE = ASCII_LAST_CHAR - ASCII_FIRST_CHAR;

static const size_t FILE_CHUNK = 1024;
static const size_t WORD_MAX_LEN = FILE_CHUNK;
/**
 * WORD_MAX_LEN est égal à la taille d'un chunk pour la raison suivante :
 * Lors de l'analyse d'un fichier texte, il n'est pas possible de comparer un mot plus grand que le chunk analysé.
 **/

int generate_text(size_t text_len, size_t alphabet_length, const char * file_path);
int generate_words(size_t word_nb, size_t word_len, size_t alphabet_length, const char * file_path);

#endif //ADT_TP1_GENERATOR_H
