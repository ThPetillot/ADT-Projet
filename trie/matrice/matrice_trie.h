#ifndef ADT_TP1_TRIE_TYPES_H
#define ADT_TP1_TRIE_TYPES_H

#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct _trie {
    int maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    int **transition; /* matrice de transition */
    char *finite; /* etats terminaux */
};

typedef struct _trie *Trie;

Trie createTrie(unsigned int maxNode);
void deleteTrie(Trie *trie);
void insertInTrie(Trie trie, unsigned char *w);
int isInTrie(Trie trie, unsigned char *w);


#endif //ADT_TP1_TRIE_TYPES_H
