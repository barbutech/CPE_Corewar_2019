/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** my_modified_getnbr.c
*/

#include "../../include/op.h"
#include <stdio.h>

int my_modified_getnbr(char *str, int *count)
{
    int result = 0;
    int neg = 0;

    if (str[(*count)] == 'r' || str[(*count)] == DIRECT_CHAR)
        (*count)++;
    if (str[(*count)] == '-') {
        neg = 1;
        (*count)++;
    }
    for (; str[(*count)] != ' ' && str[(*count)] != '\t' &&
    str[(*count)] != '\0' && str[(*count)] != '\n' &&
    str[(*count)] != SEPARATOR_CHAR &&
    str[(*count)] != COMMENT_CHAR; (*count)++)
        result = result * 10 + (str[(*count)] - 48);
    if (neg == 1)
        result = -result;
    return (result);
}