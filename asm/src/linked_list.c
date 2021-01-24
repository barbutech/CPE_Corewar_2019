/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** linked_list.c
*/

#include "../include/my.h"
#include "../../include/op.h"

void stack_push(general_t **general, char *value)
{
    general_t *new = malloc(sizeof(general_t));

    new->line = my_strdup(value);
    new->next = NULL;
    new->nbr_labels_to_search = 0;
    new->line_size = 0;

    if (!(*general)) {
        new->head = new;
        (*general) = new;
        return ;
    }
    new->head = (*general)->head;
    new->prev = (*general);
    (*general) = new;
    (*general)->prev->next = (*general);
    return ;
}

void make_links_between_nodes(index_t **index, index_t *new)
{
    if (!(*index)) {
        new->head = new;
        new->id = 0;
        (*index) = new;
        return ;
    }
    new->head = (*index)->head;
    new->prev = (*index);
    new->id = (*index)->id + 1;
    (*index) = new;
    (*index)->prev->next = (*index);
    return ;
}

void index_label(index_t **index, general_t *general, int *count, int tempo)
{
    index_t *new = malloc(sizeof(index_t));

    new->search_label = malloc(sizeof(char) * (tempo + 1));
    new->label_instruct = NULL;
    if (new->search_label == NULL) return ;
    for (int pos = 0; general->line[(*count)] != ' ' &&
    general->line[(*count)] != SEPARATOR_CHAR &&
    general->line[(*count)] != '\t' && general->line[(*count)] != '\0' &&
    general->line[(*count)] != '\n'; (*count)++, pos++)
        new->search_label[pos] = general->line[(*count)];
    new->search_label[tempo] = '\0';
    new->next = NULL;

    make_links_between_nodes(index, new);
    return ;
}

int clear_before_action(char *line, int *count, index_t *new)
{
    int size = 0;
    int tmp = 0;
    new->next = NULL;
    new->label_instruct = NULL;
    new->search_label = NULL;

    for (; line[(*count)] != '\0' &&
    line[(*count)] != '\t' && line[(*count)] != ' ' && line[(*count)] != '\n' &&
    line[(*count)] != LABEL_CHAR; (*count)++) {
        for (tmp = 0; LABEL_CHARS[tmp] != '\0'; tmp++)
            if (LABEL_CHARS[tmp] == line[(*count)]) {
                size++;
                break;
            }
        if (LABEL_CHARS[tmp] == '\0') return (-1);
    }
    if (size == 0) return (0);
    new->label_instruct = malloc(sizeof(char) * (size + 1));
    new->label_instruct[size] = '\0';
    return (1);
}

int index_this(index_t **index, int *count, char *line)
{
    int size = 0;
    int ret = 0;
    int pos = (*count);
    index_t *new = malloc(sizeof(index_t));

    if ((ret = clear_before_action(line, count, new)) != 1) return (ret);
    for (; pos < (*count); pos++, size++)
        new->label_instruct[size] = line[pos];
    if (!(*index)) {
        new->head = new;
        new->id = 0;
        (*index) = new;
        return (0);
    }
    new->head = (*index)->head;
    new->prev = (*index);
    new->id = (*index)->id + 1;
    (*index) = new;
    (*index)->prev->next = (*index);
    return (0);
}