cmake_minimum_required(VERSION 3.8)
project(ADT_TP1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c
        trie/hach/hach_trie.h trie/hach/hach_trie.c
        trie/utilities/trie_utilities.c trie/utilities/trie_utilities.h
        text/generator.c text/generator.h
        text/search.c text/search.h text/analyse.c text/analyse.h)

add_executable(ADT_TP1 ${SOURCE_FILES})
