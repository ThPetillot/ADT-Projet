#include <stdio.h>
#include <time.h>

#include "text/search.h"
#include "text/analyse.h"

void duration_search(const char * funName, int (*fun)(const char *, size_t, const char *, size_t)
        , const char * w, size_t wLen, const char * text, size_t textLen);

int main(int argc, char *argv[]) {
    /*
    const char * w = "ba";
    const char * text = "abab";

    size_t wLen = strlen(w);
    size_t textLen = strlen(text);

    //duration_search("searchNBi", searchNBi, w, wLen, text, textLen);
    //duration_search("searchNBir", searchNBir, w, wLen, text, textLen);
    //duration_search("searchNBirSen", searchNBirSen, w, wLen, text, textLen);
    duration_search("searchNBirSen", searchNBirSen, w, wLen, text, textLen);
    duration_search("Morris & Pratt", morrisPratt, w, wLen, text, textLen);

    //*/

    //*

    char * text_path = "/Users/thomaspetillot/Desktop/text.txt";
    char * words_path = "/Users/thomaspetillot/Desktop/words.txt";
    size_t alphabet_length = 2;
    size_t text_len = 5000000;
    size_t words_nb = 5;
    size_t word_len = 15;

    srand(time(NULL));
    // Génération des fichiers
    if (generate_text(text_len, alphabet_length, text_path) == -1)
        return -1;

    if (generate_words(words_nb, word_len, alphabet_length, words_path) == -1)
        return -1;

    //*
    printf("searchNBi : \n");
    analyse(text_path, words_path,
            alphabet_length, text_len,
            words_nb, word_len,
            searchNBi);
    printf("\n");
    /*
    printf("searchNBir : \n");
    analyse(text_path, words_path,
            alphabet_length, text_len,
            words_nb, word_len,
            searchNBir);
    printf("\n");
    //*/
    /*
    printf("searchNBirSen : \n");
    analyse(text_path, words_path,
            alphabet_length, text_len,
            words_nb, word_len,
            searchNBirSen);
    printf("\n");
    //*/
    //*
    printf("searchNCmpBrSen : \n");
    analyse(text_path, words_path,
            alphabet_length, text_len,
            words_nb, word_len,
            searchNCmpBrSen);
    printf("\n");
    //*/
    /*
    printf("Morris&Pratt : \n");
    analyse(text_path, words_path,
            alphabet_length, text_len,
            words_nb, word_len,
            morrisPratt);
    printf("\n");
    //*/

    printf("Knuth&Morris&Pratt : \n");
    analyse(text_path, words_path,
            alphabet_length, text_len,
            words_nb, word_len,
            knuthMorrisPratt);
    //*/


    return 0;
}


void duration_search(const char *funName, int (*fun)(const char *, size_t, const char *, size_t)
        , const char * w, size_t wLen, const char * text, size_t textLen) {

    clock_t begin, end;

    begin = clock();
    int occ = fun(w, wLen, text, textLen);
    end = clock();

    printf("%s execution : \n", funName);
    printf("\t%d occurence of %s in the given text\n", occ, w);
    printf("\tduration : %f ms\n", time_spent(begin, end));
    printf("\n");
}