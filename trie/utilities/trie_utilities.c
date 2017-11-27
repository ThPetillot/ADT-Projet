#include "trie_utilities.h"

#include <stdio.h>
#include <string.h>
#define MAX_NODE 100

Trie prefixe(unsigned char * w) {
    Trie trie = createTrie(MAX_NODE);
    size_t wlen = strlen((const char *) w);

    unsigned char pw[wlen];

    for (int i = 0; i < wlen; ++i) {
        strncat((char *) pw, (const char *) w + (i * sizeof(unsigned char)), 1);
        insertInTrie(trie, pw);
    }

    return trie;
}

void insertSuffixe(Trie trie, unsigned char * w) {
    size_t wlen = strlen((const char *) w);

    unsigned char pw[wlen];

    for (int i = 0; i < wlen; ++i) {
        memset(pw, 0, wlen);
        size_t start = (wlen - 1 - i) * sizeof(unsigned char);
        strncat((char *) pw,(const char *) (w + start), i + 1);

        printf("insert : %s\n", pw);
        insertInTrie(trie, pw);
    }
}

Trie suffixe(unsigned char * w) {
    Trie trie = createTrie(MAX_NODE);
    insertSuffixe(trie, w);
    return trie;
}


Trie facteur(unsigned char * w) {
    Trie trie = createTrie(MAX_NODE);
    size_t wlen = strlen((const char*) w);

    unsigned char pw[wlen];

    for (int i = 0; i < wlen; ++i) {
        strncat((char *) pw, (const char *) w + (i * sizeof(unsigned char)), 1);
        insertSuffixe(trie, pw);
    }

    return trie;
}