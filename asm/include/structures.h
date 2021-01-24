/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** structures.h
*/

#ifndef struct_h
#define struct_h

struct general {
    char *line;
    int *command;
    int *type;
    int is_label;
    int line_size;
    int nbr_labels_to_search;
    int nbr_instruct;
    int coding_byte;
    struct general *next;
    struct general *prev;
    struct general *head;
};

typedef struct general general_t;

struct index {
    char *search_label;
    char *label_instruct;
    int id;
    struct index *next;
    struct index *prev;
    struct index *head;
};

typedef struct index index_t;

#endif