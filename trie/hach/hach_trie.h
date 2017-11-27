#ifndef ADT_TP1_HACH_TRIE_H
#define ADT_TP1_HACH_TRIE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct _list {
    int startNode, /* etat de depart de la transition */
            targetNode; /* cible de la transition */
    unsigned char letter; /* etiquette de la transition */
    struct _list *next; /* maillon suivant */
};

typedef struct _list *List;

struct _trie {
    int maxNode; /* Nombre maximal de noeuds du trie */
    int nextNode; /* Indice du prochain noeud disponible */
    List *transition; /* listes d’adjacence */
    char *finite; /* etats terminaux */
};

typedef struct _trie *Trie;

Trie createTrie(unsigned int maxNode);
void deleteTrie(Trie *trie);
void insertInTrie(Trie trie, unsigned char *w);
void debugTrie(Trie trie);
int isInTrie(Trie trie, unsigned char *w);

#endif //ADT_TP1_HACH_TRIE_H
