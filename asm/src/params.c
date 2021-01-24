/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** params.c
*/

#include "../../include/op.h"
#include "../include/my.h"

int param_type(general_t *general, int count, int pos, header_t **header)
{
    if (general->line[count] == 'r') {
        general->type[pos] = 1;
        general->coding_byte = (general->coding_byte << 2) | 1;
        (*header)->prog_size += 1;
        general->line_size += 1;
        return (T_REG);
    }
    if (general->line[count] == DIRECT_CHAR) {
        general->type[pos] = DIR_SIZE;
        general->coding_byte = (general->coding_byte << 2) | 2;
        return (T_DIR);
    }
    general->type[pos] = IND_SIZE;
    general->coding_byte = (general->coding_byte << 2) | 3;
    (*header)->prog_size += IND_SIZE;
    general->line_size += IND_SIZE;
    return (T_IND);
}

int pass_before_instructions(char *str, int count)
{
    for (; str[count] == ' ' || str[count] == '\t' ||
    str[count] == SEPARATOR_CHAR; count++);
    for (; str[count] != ' ' && str[count] != '\t' &&
    str[count] != SEPARATOR_CHAR; count++);
    return (count);
}

void header_to_big_endian(header_t *header)
{
    header->magic = COREWAR_EXEC_MAGIC;
    header->magic = ((header->magic >> 24) & 0xff) | ((header->magic << 8) &
    0xff0000) | ((header->magic >> 8) & 0xff00) | ((header->magic << 24)
    & 0xff000000);
    header->prog_size = ((header->prog_size >> 24) & 0xff) |
    ((header->prog_size << 8) & 0xff0000) | ((header->prog_size >> 8) &
    0xff00) | ((header->prog_size << 24) & 0xff000000);
}