//
// Created by Thomas Petillot on 21/11/2017.
//

#include "analyse.h"

double time_spent(clock_t begin, clock_t end);

int count_word_in_file(const char * word, const char * path,
                       int (*count_occ)(const char *, size_t, const char *, size_t));

/**
 * Génère deux fichiers textes sur un alphabet de taille alphabet_length.
 * Le premier (à text_path) contient un texte de longueur text_len.
 * Le deuxième (à words_path) contient words_nb mot(s) de longueur word_len.
 *
 * Ensuite, affiche le nombre de d'occurence de chaque mot du fichier de mots dans le fichier texte.
 * Le nombre d'occurence est calculé à l'aide de la fonction count_occ.
 *
 * @param text_path
 * @param words_path
 * @param alphabet_length
 * @param text_len
 * @param words_nb
 * @param word_len
 * @param count_occ
 * @return
 */
int analyse(const char * text_path, const char * words_path,
            size_t alphabet_length, size_t text_len,
            size_t words_nb, size_t word_len,
            int (*count_occ)(const char *, size_t, const char *, size_t)) {

    // Ouverture du fichier
    FILE * file = fopen(words_path, "r");
    if (file == NULL)
        return -1;

    // Informations
    printf("Alphabet size : %zu | Text length : %zu | Pattern length : %zu\n",
           alphabet_length, text_len, word_len);

    // Comptage et affichage des occurences
    char * word = NULL;
    size_t wLen = 0;
    clock_t begin, end;

    double total_spent = 0;
    while (getline(&word, &wLen, file) != -1) {
        strtok(word, "\r\n");

        begin = clock();
        int count = count_word_in_file(word, text_path, count_occ);
        end = clock();

        double spent = time_spent(begin, end);
        total_spent += spent;
        printf("\t%s : occurrences(%d)\t time(%fs)\n", word, count, spent);
    }
    printf("-> total time spent %fs\n", total_spent);

    // Libération des ressources
    fclose(file);
    if (word) {
        free(word);
    }

    return 0;
}

/**
 * Retourne le nombre d'occurence de word dans le fichier localisé à path.
 * Utilise la fonction count_occ pour effectuer le comptage.
 *
 * @param word
 * @param path
 * @param count_occ
 * @return
 */
int count_word_in_file(const char * word, const char * path,
                       int (*count_occ)(const char *, size_t, const char *, size_t)) {

    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("Search failed : fopen return NULL\n");
    }

    char * chunk = malloc(sizeof(char) * FILE_CHUNK);
    size_t wLen = strlen(word);

    size_t read;
    int occ = 0;
    while ((read = fread(chunk, sizeof(char), FILE_CHUNK, file)) >= FILE_CHUNK) {
        occ += count_occ(word, wLen, chunk, read);
        fseek(file, -(wLen - 1), SEEK_CUR);
        memset(chunk, '\0', FILE_CHUNK);
    }

    occ += count_occ(word, wLen, chunk, read);

    fclose(file);
    free(chunk);

    return occ;
}

/**
 * Donne le temps entre begin et end en secondes.
 * @param begin
 * @param end
 * @return
 */
double time_spent(clock_t begin, clock_t end) {
    return (double)(end - begin) / (CLOCKS_PER_SEC);
}