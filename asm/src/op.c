/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** op.c
*/


#include "../../include/op.h"
#include "../include/my.h"

op_t    op_tab[] =
{
    {"live", 1, {T_DIR}, 1, 10, "alive"},
    {"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load"},
    {"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store"},
    {"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition"},
    {"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction"},
    {"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
    "et (and  r1, r2, r3   r1&r2 -> r3"},
    {"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
    "ou  (or   r1, r2, r3   r1 | r2 -> r3"},
    {"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
    "ou (xor  r1, r2, r3   r1^r2 -> r3"},
    {"zjmp", 1, {T_DIR}, 9, 20, "jump if zero"},
    {"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
    "load index"},
    {"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
    "store index"},
    {"fork", 1, {T_DIR}, 12, 800, "fork"},
    {"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
    "long load index"},
    {"lfork", 1, {T_DIR}, 15, 1000, "long fork"},
    {"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load"},
    {"aff", 1, {T_REG}, 16, 2, "aff"},
    {0, 0, {0}, 0, 0, 0}
};

int value_label(general_t *general, index_t *index, int tmp)
{
    index_t *node_to_search = index;
    int nbr_labels = 0;
    char *to_find = my_strdup(index->search_label);

    for (index = index->head; index; index = index->next) {
        if (index->label_instruct &&
        (my_strcmp(index->label_instruct, to_find) == 0))
            break;
        if (!(index->next)) return (-1);
    }
    if (node_to_search->id > index->id) {
        for (; node_to_search->id > index->id; index = index->next)
            if (index->label_instruct) nbr_labels++;
        return (go_back(general, tmp, nbr_labels));
    }
    else if (node_to_search->id < index->id) {
        for (; index->id > node_to_search->id; index = index->prev)
            if (index->label_instruct) nbr_labels++;
        return (go_ahead(general, tmp, nbr_labels));
    }
    return (0);
}

int copy_the_label(general_t *general, int *count, index_t **index)
{
    (*count)++;
    int tmp = (*count);
    int tempo = 0;


    for (; general->line[tmp] != ' ' && general->line[tmp] != '\t' &&
    general->line[tmp] != SEPARATOR_CHAR &&
    general->line[tmp] != '\0' && general->line[tmp] != '\n' &&
    general->line[tmp] != LABEL_CHAR; tmp++);
    if (general->line[tmp] == LABEL_CHAR)
        return (84);
    tempo = tmp - (*count);
    if (tempo == 0)
        return (84);
    index_label(index, general, count, tempo);
    return (0);
}

int call_label(general_t *general, int count, index_t **index)
{
    for (; general->line[count - 1] != '\0' &&
    general->line[count] != '\0'; count++) {
        if (general->line[count] == LABEL_CHAR)
            if (copy_the_label(general, &count, index) == 84) return (84);
    }
    return (0);
}

int case_labels(general_t *general, index_t **index)
{
    general = general->next;
    int count = 0;

    for (; general; general = general->next) {
        count = 0;
        if ((general->is_label = search_lab(general->line, &count, index)) < 0)
            return (84);
        count++;
        if (general->line[count] == '\0' || general->line[count] == '\n')
            continue;
        if (call_label(general, count, index) == 84)
            return (84);
    }
    return (0);
}