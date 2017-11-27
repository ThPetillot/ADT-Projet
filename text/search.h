#ifndef ADT_TP1_SEARCH_H
#define ADT_TP1_SEARCH_H

#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../trie/utilities/trie_utilities.h"

/**
 * N    : Naive
 * B[i, r]   : Boucle [interne, rapide]
 * Sen  : Sentinelle
 * Cmp  : strncmp
 */

int searchNBi(const char * w, size_t wLen, const char * text, size_t textLen);
int searchNBir(const char * word, size_t wordLen, const char * text, size_t textLen);
int searchNBirSen(const char * word, size_t wordLen, const char * text, size_t textLen);

int searchNCmp(const char * w, size_t wLen, const char * text, size_t textLen);
int searchNCmpBr(const char * word, size_t wordLen, const char * text, size_t textLen);
int searchNCmpBrSen(const char * word, size_t wordLen, const char * text, size_t textLen);

int morrisPratt(const char * word, size_t wordLen, const char * text, size_t textLen);
int knuthMorrisPratt(const char * word, size_t wordLen, const char * text, size_t textLen);

/*
int boyerMoore(char * word, char * text);
int horspool(char * word, char * text);
int quick(char * word, char * text);
 */


#endif //ADT_TP1_SEARCH_H
