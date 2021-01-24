/*
** EPITECH PROJECT, 2020
** CPE_lemin_2019
** File description:
** The my_strcmp file.
*/

#include "../include/my.h"

int my_strcmp(char *s1, char *s2)
{
    int m = 0;
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
        i = i + 1;
    m = s1[i] - s2[i];
    return (m);
}