/*
** EPITECH PROJECT, 2019
** clone
** File description:
** navigate.c
*/

#include "../include/my.h"

int go_back(general_t *general, int tmp, int nbr_labels)
{
    general->command[tmp] = 0;
    int ret = 0;

    general = general->prev;
    for (int count = 0; count < nbr_labels; general = general->prev) {
        if (general->is_label == 1)
            count++;
        ret -= general->line_size;
        if (general->prev == NULL)
            return (-1);
    }
    return (ret);
}

int go_ahead(general_t *general, int tmp, int nbr_labels)
{
    general->command[tmp] = 0;
    int ret = 0;

    for (int count = 0; count < nbr_labels; general = general->next) {
        if (general->is_label == 1)
            count++;
        ret += general->line_size;
        if (general->next == NULL)
            return (-1);
    }
    return (ret);
}

int replace_label(general_t **general, int tempo, index_t **index, int *nbr)
{
    int count = 0;

    if ((*general)->line[tempo] == LABEL_CHAR) {
        for (; (*general)->command[count] != -2 &&
        (*general)->command[count] != -1; count++);
        (*general)->command[count] = value_label((*general), (*index), count);
        (*index) = (*index)->next;
        (*nbr)++;
        if ((*general)->command[count] == -1) return (84);
    }
    return (0);
}

int track_label(general_t **general, index_t **index)
{
    int nbr = 0;

    for (int tempo = 0; (*general)->line[tempo] != '\0' &&
    nbr < (*general)->nbr_labels_to_search; tempo++)
        if (replace_label(general, tempo, index, &nbr) == 84)
            return (84);
    return (0);
}

int turn_of_labels(general_t *general, index_t *index)
{
    if (index == NULL)
        return (0);
    index = index->head;

    for (general = general->next; general; general = general->next) {
        if (general->is_label == 1) {
            index = index->next;
            continue;
        }
        if (general->nbr_labels_to_search > 0)
            if (track_label(&general, &index) == 84) return (84);
    }
    return (0);
}