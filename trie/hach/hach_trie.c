#include "hach_trie.h"

#define START_NODE 0

int simpleHash(int node, unsigned char c, unsigned int nodeNb);
List createListNode(int startNode, int targetNode, char letter);

/**
 * Crée et initialise le Trie.
 * @param maxNode
 * @pre maxNode >= 0
 * @return:
 *  NULL en cas d'échec
 *  Trie sinon
 */

Trie createTrie(unsigned int maxNode) {
    Trie trie = malloc(sizeof(*trie));

    trie->maxNode = maxNode;
    trie->nextNode = START_NODE + 1;

    size_t nodeNb = maxNode + 1;

    size_t transitionSize = sizeof(List) * nodeNb;
    trie->transition = malloc(transitionSize);
    for (int i = 0; i < nodeNb; i++) {
        trie->transition[i] = NULL;
    }

    size_t finiteSize = sizeof(char) * nodeNb;
    trie->finite = malloc(finiteSize);
    memset(trie->finite, false, finiteSize);

    return trie;
}

/**
 * Supprime proprement le Trie.
 * @param trie
 */
void deleteTrie(Trie * trie) {
    free((*trie)->finite);

    for(int i = 0; i < (*trie)->maxNode + 1; ++i) {
        List list = (*trie)->transition[i];
        while (list != NULL) {
            List nextList = list->next;
            free(list);
            list = nextList;
        }
    }

    free((*trie)->transition);
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

    int currentNode = 0;
    size_t wLen = strlen((const char *) w);
    int nodeNb = trie->maxNode + 1;
    List list;
    
    for (int i = 0; i < wLen; i++) {
        unsigned char c = w[i];
        int hashes = simpleHash(currentNode, c, nodeNb);
        
        list = trie->transition[hashes];
        List * pre = &trie->transition[hashes];

        while(list != NULL) {
            if (list->letter == c && list->startNode == currentNode) {
                currentNode = list->targetNode;
                break;
            } else {
                pre = &list->next;
                list = list->next;
            }
        }

        if (currentNode > trie->maxNode) {
            printf("Le noeud courrant a dépassé la taille de noeud maximum.\n");
            return;
        }

        if (list == NULL) {
            list = createListNode(currentNode, currentNode + 1, c);
            ++currentNode;
            *pre = list;
        }
    }

    trie->finite[list->startNode] = true;
}

/**
 * Crée et initialise un noeud de List.
 * @param startNode
 * @param targetNode
 * @param letter
 * @return
 */
List createListNode(int startNode, int targetNode, char letter) {
    List list = malloc(sizeof(*list));
    list->startNode = startNode;
    list->targetNode = targetNode;
    list->next = NULL;
    list->letter = letter;

    return list;
}

/**
 * Indique le mot w est dans le Trie.
 * @param trie
 * @param w
 * @return
 */
int isInTrie(Trie trie, unsigned char *w) {
    size_t wLen = strlen((const char *) w);
    int currentNode = 0;
    int nodeNb = trie->maxNode + 1;
    List list = NULL;

    for (int i = 0; i < wLen; i++) {
        unsigned char c = w[i];
        int hachIndice = simpleHash(currentNode, c, nodeNb);

        list = trie->transition[hachIndice];
        while(list != NULL) {
            if (list->letter == c && list->startNode == currentNode) {
                currentNode = list->targetNode;
                break;
            } else {
                list = list->next;
            }
        }

        if (list == NULL) {
            return false;
        }
    }

    if (trie->finite[list->startNode]) {
        return true;
    }

    return 0;
}

// Tools

/**
 * Associe un hashcode à un couple noeud/caractère.
 * @param etat
 * @param c
 * @return int
 */

int simpleHash(int node, unsigned char c, unsigned int nodeNb) {
    return (node*21 + c)%nodeNb;
}

/**
 * Affiche en console le Trie.
 * @param trie
 */
void debugTrie(Trie trie) {
    for(int i = 0; i < (trie->maxNode + 1); i++) {
        List list = trie->transition[i];

        printf("%d\t:\t", i);

        if (list == NULL) {
            printf("X");
        }

        while(list != NULL) {
            printf("[%d][%c][%d] ->", list->startNode, list->letter, list->targetNode);
            list = list->next;
        }
        printf("\n");
    }
}