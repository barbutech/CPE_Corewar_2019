/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** my_strdup.c
*/

#include "../include/my.h"

char *my_strdup(char *str)
{
    int size = my_strlen(str);
    char *ret = malloc(sizeof(char) * (size + 1));

    for (int count = 0; count < size; count++)
        ret[count] = str[count];
    ret[size] = '\0';
    return (ret);
}