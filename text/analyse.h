#ifndef ADT_TP1_ANALYSE_H
#define ADT_TP1_ANALYSE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "generator.h"
#include "search.h"

int analyse(const char * text_path, const char * words_path,
            size_t alphabet_length, size_t text_len,
            size_t words_nb, size_t word_len,
            int (*count_occ)(const char *, size_t, const char *, size_t));

double time_spent(clock_t begin, clock_t end);

#endif //ADT_TP1_ANALYSE_H
