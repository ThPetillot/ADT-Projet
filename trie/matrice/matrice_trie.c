#include "matrice_trie.h"

#define EMPTY_TRANSITION 0
#define START_NODE 0

/**
 * Crée et initialise le Trie.
 * @param maxNode
 * @pre maxNode >= 0
 * @return Trie
 */
Trie createTrie(unsigned int maxNode) {
    Trie trie = malloc(sizeof(*trie));

    trie->maxNode = maxNode;
    trie->nextNode = START_NODE + 1;

    size_t nodeNb = maxNode + 1;
    size_t finiteSize = sizeof(char) * nodeNb;
    trie->finite = malloc(finiteSize);

    memset(trie->finite, false, finiteSize);

    trie->transition = malloc(sizeof(int *) * nodeNb);
    for (int i = 0; i < nodeNb; i++) {
        size_t transitionSize = UCHAR_MAX * sizeof(int);
        trie->transition[i] = malloc(transitionSize);
        memset(trie->transition[i], EMPTY_TRANSITION, transitionSize);
    }

    return trie;
}

/**
 * Supprime proprement le Trie.
 * @param trie
 */
void deleteTrie(Trie *trie) {
    size_t nodeNb = (size_t) (*trie)->maxNode + 1;
    for (int i = 0; i < nodeNb; i++) {
        free((*trie)->transition[i]);
    }
    free((*trie)->transition);
    free((*trie)->finite);
    free(*trie);

    *trie = NULL;
}

/**
 * Insert le mot w dans le Trie.
 * @param trie
 * @param w
 */
void insertInTrie(Trie trie, unsigned char *w) {
    printf("-- insert %s in the trie. --\n", w);

    if (isInTrie(trie, w)) {
        return;
    }

    size_t sizeW = strlen((const char *) w);
    int currentNode = 0;

    for (int i = 0; i < sizeW; ++i) {
        int c = (int) w[i];

        if (trie->transition[currentNode][c] != EMPTY_TRANSITION) {
            currentNode = trie->transition[currentNode][c];
        } else {
            trie->transition[currentNode][c] = trie->nextNode;
            currentNode = trie->nextNode;
            ++trie->nextNode;
        }

        if (currentNode > trie->maxNode) {
            printf("Failed to insert \"%s\" [Not enought nodes]\n", w);
            return;
        }
    }

    trie->finite[currentNode] = true;

}

/**
 * Indique si le mot w est dans le Trie.
 * @param trie
 * @param w
 * @return bool
 */
int isInTrie(Trie trie, unsigned char *w) {
    size_t sizeW = strlen((const char *) w);

    if (sizeW > trie->maxNode) {
        printf("\"%s\"  Can't be in the trie [Not enought nodes]\n", w);
        return false;
    }

    int currentNode = 0;

    for (int i = 0; i < sizeW ; ++i) {
        unsigned char c = w[i];

        if (trie->transition[currentNode][c] != EMPTY_TRANSITION) {
            currentNode = trie->transition[currentNode][c];
        } else {
            return false;
        }
    }

    return trie->finite[currentNode];
}