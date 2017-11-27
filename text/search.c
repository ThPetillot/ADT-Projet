#include "search.h"

#define consistancy(wordLen, textLen) ((wordLen > textLen) ? (true) : (false))

/**
 * Boucle interne définissant w == text[index ... index + wLen]
 *
 * @param w
 * @param wLen
 * @param text
 * @param index
 * @return
 */
int internal_loop(const char * w, size_t wLen, const char * text, int index) {
    size_t i = 0;
    while (i < wLen && w[i] == text[index + i]) {
        i++;
    }

    if (i >= wLen) {
        return true;
    }

    return false;
}

/**
 * Recherche naive avec boucle interne.
 * @param w
 * @param wLen
 * @param text
 * @param textLen
 * @return
 */
int searchNBi(const char * w, size_t wLen, const char * text, size_t textLen) {
    if (consistancy(wLen, textLen)) {
        return 0;
    }
    int occ = 0;
    int i = 0;
    while (i <= textLen - wLen) {
        if (internal_loop(w, wLen, text, i)) {
            occ++;
        }
        i++;
    }
    return occ;
}

/**
 * Recherche Naive avec boucle interne rapide.
 * @param w
 * @param wLen
 * @param text
 * @param textLen
 * @return
 */
int searchNBir(const char * w, size_t wLen, const char * text, size_t textLen) {
    if (consistancy(wLen, textLen)) {
        return 0;
    }

    int occ = 0;
    int i = 0;


    size_t j = wLen - 1;
    int c = w[j];

    while ((i+j) < textLen) {
        while((i+j) < textLen && c != text[i + j]) {
            i++;
        }

        if (internal_loop(w, wLen, text, i)) {
            occ++;
        }

        i++;
    }

    return occ;
}


/**
 * Recherche Naive avec boucle interne rapide et sentinelle
 * @param word
 * @param text
 * @return
 */
int searchNBirSen(const char * w, size_t wLen, const char * text, size_t textLen) {
    if (consistancy(wLen, textLen)) {
        return 0;
    }

    char * sentinelle = malloc(sizeof(char) * (textLen + wLen));
    memcpy(sentinelle, text, textLen);
    memcpy(sentinelle + textLen, w, wLen);

    int occ = 0;
    int i = 0;

    size_t j = wLen - 1;
    char c = w[j];

    while (1) {
        while(c != sentinelle[i + j]) {
            i++;
        }

        if (internal_loop(w, wLen, sentinelle, i)) {
            if (i >= textLen - j) {
                break;
            }
            occ++;
        }

        i++;
    }

    free(sentinelle);
    return occ;
}


/**
 * Recherche Naive avec strncmp
 * @param word
 * @param text
 * @return
 */
int searchNCmp(const char * w, size_t wLen, const char * text, size_t textLen) {
    if (consistancy(wLen, textLen)) {
        return 0;
    }

    int occ = 0;
    int i = 0;

    while (i <= textLen - wLen) {
        if (strncmp(w, text + (i*sizeof(char)), wLen) == 0) {
            occ++;
        }
        i++;
    }

    return occ;
}


/**
 * Recherche Naive avec strncmp et boucle rapide
 * @param w
 * @param wLen
 * @param text
 * @param textLen
 * @return
 */
int searchNCmpBr(const char * w, size_t wLen, const char * text, size_t textLen) {
    if (consistancy(wLen, textLen)) {
        return 0;
    }

    int occ = 0;
    int i = 0;


    size_t j = wLen - 1;
    int c = w[j];

    while ((i+j) < textLen) {
        while((i+j) < textLen && c != text[i + j]) {
            i++;
        }

        if (strncmp(w, text + (i*sizeof(char)), wLen) == 0) {
            occ++;
        }

        i++;
    }

    return occ;
}

/**
 * Recherche Naive avec strncmp, boucle rapide et sentinelle
 * @param w
 * @param wLen
 * @param text
 * @param textLen
 * @return
 */
int searchNCmpBrSen(const char * w, size_t wLen, const char * text, size_t textLen) {
    if (consistancy(wLen, textLen)) {
        return 0;
    }

    char * sentinelle = malloc(sizeof(char) * (textLen + wLen));
    memcpy(sentinelle, text, textLen);
    memcpy(sentinelle + textLen, w, wLen);

    int occ = 0;
    int i = 0;

    size_t j = wLen - 1;
    char c = w[j];

    while (1) {
        while(c != sentinelle[i + j]) {
            i++;
        }

        if (strncmp(w, sentinelle + (i*sizeof(char)), wLen) == 0) {
            if (i >= textLen - j) {
                break;
            }
            occ++;
        }

        i++;
    }

    free(sentinelle);
    return occ;
}


void preMp(const char * w, size_t wLen, int mpNext[]) {
    int i = 0;
    int j = mpNext[0] = -1;

    while(i < wLen) {
        while (j > -1 && w[i] != w[j]) {
            j = mpNext[j];
        }

        mpNext[++i] = ++j;
    }
}

/**
 * Algorithme de Morris&Pratt
 * @param w
 * @param wLen
 * @param text
 * @param textLen
 * @return
 */
int morrisPratt(const char * w, size_t wLen, const char * text, size_t textLen) {
    int mpNext[wLen];

    // Preprocessing
    preMp(w, wLen, mpNext);

    int i, j, occ;
    occ = i = j = 0;

    while (j < textLen) {
        while (i > -1 && w[i] != text[j]) {
            i = mpNext[i];
        }

        i++;
        j++;
        if (i >= wLen) {
            occ++;
            i = mpNext[i];
        }
    }

    return occ;
}


void preKmp(char *w, size_t wLen, int kmpNext[]) {
    int i, j;

    i = 0;
    j = kmpNext[0] = -1;
    while (i < wLen) {
        while (j > -1 && w[i] != w[j])
            j = kmpNext[j];
        i++;
        j++;
        if (w[i] == w[j])
            kmpNext[i] = kmpNext[j];
        else
            kmpNext[i] = j;
    }
}

/**
 * Algorithme de Morris&Pratt
 * @param w
 * @param wLen
 * @param text
 * @param textLen
 * @return
 */
int knuthMorrisPratt(const char * w, size_t wLen, const char * text, size_t textLen) {
    int occ, i, j, kmpNext[wLen];

    /* Preprocessing */
    preKmp(w, wLen, kmpNext);

    /* Searching */
    occ = i = j = 0;
    while (j < textLen) {
        while (i > -1 && w[i] != text[j])
            i = kmpNext[i];
        i++;
        j++;
        if (i >= wLen) {
            occ++;
            i = kmpNext[i];
        }
    }

    return occ;
}

int boyerMoore(char * word, char * text);
int horspool(char * word, char * text);
int quick(char * word, char * text);