/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** others.c
*/

#include "../include/my.h"

void convert_type(general_t *general, int count)
{
    if (general->type[count] == 2) {
        if (general->command[count] < 0) {
            general->command[count] = ((general->command[count] << 8) &
            0xff00) | ((general->command[count] >> 8) & 0xff);
        }
        else
            general->command[count] = (general->command[count] << 8) |
            (general->command[count] >> 24);
    }
    else if (general->type[count] == 4) {
        general->command[count] = ((general->command[count] >> 24) &
        0xff) | ((general->command[count] << 8) &
        0xff0000) | ((general->command[count] >> 8) & 0xff00) |
        ((general->command[count] << 24)
        & 0xff000000);
    }
}

int is_a_label_here(general_t **general, int *count, int tmp, index_t **index)
{
    if ((*general)->line[(*count) + 1] == LABEL_CHAR) {
        (*general)->nbr_labels_to_search++;
    if ((*general)->command[tmp] == -1)
        return (84);
    (*general)->command[tmp] = -2;
    (*count) += (my_strlen((*index)->search_label) + 2);
    (*index) = (*index)->next;
    }
    else
        (*general)->command[tmp] = my_modified_getnbr((*general)->line, count);
    return (0);
}

int correct_byte(general_t **general, int pos, header_t **header)
{
    int dec = 8 - (((*general)->nbr_instruct - 1) * 2);

    (*general)->coding_byte = (*general)->coding_byte << dec;
    if (pos  == 0 || pos == 8 || pos == 11 || pos == 13)
        (*general)->coding_byte = 0;
    if ((*general)->coding_byte != 0) {
        (*general)->line_size++;
        (*header)->prog_size++;
    }
    return (0);
}

int type_param(general_t **general, int type, int tmp, header_t **header)
{
    int pos = 0;

    while (check_first_word((*general)->line, op_tab[pos].mnemonique) != 0)
        pos++;
    if (type == T_REG)
        if ((*general)->command[tmp] < 1 ||
        (*general)->command[tmp] > REG_NUMBER) return (84);
    if (type == T_DIR) {
        if (pos >= 8 && pos < 14 ) {
            (*general)->line_size += 2;
            (*general)->type[tmp] = 2;
            (*header)->prog_size += 2;
        }
        else {
            (*header)->prog_size += DIR_SIZE;
            (*general)->line_size += DIR_SIZE;
        }
    }
    return (0);
}