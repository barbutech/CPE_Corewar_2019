/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** checks_name_and_com.c
*/

#include "../include/my.h"

int check_end_comm(int count, general_t **general)
{
    for (; (*general)->line[count] != '\0' &&
    (*general)->line[count] != COMMENT_CHAR &&
    (*general)->line[count] != '\n' && ((*general)->line[count] == ' ' ||
    (*general)->line[count] == '\t'); count++);
    if ((*general)->line[count] != '\0' &&
    (*general)->line[count] != COMMENT_CHAR &&
    (*general)->line[count] != ' ' && (*general)->line[count] != '\t' &&
    (*general)->line[count] != '\n')
        return (84);
    return (0);
}

int check_beginning_comm(int count, general_t **general)
{
    if (!(*general))
        return (-1);
    for (; COMMENT_CMD_STRING[count] != '\0' &&
    (*general)->line[count] != '\0'; count++)
        if ((*general)->line[count] != COMMENT_CMD_STRING[count])
            return (-1);
    if ((*general)->line[count] == '\"')
        return (-1);
    for (; (*general)->line[count] != '\0' && ((*general)->line[count] == ' ' ||
    (*general)->line[count] == '\t'); count++);
    if ((*general)->line[count] != '\"')
        return (-1);
    if ((*general)->line[count + 1] == '\0' ||
    (*general)->line[count + 1] == '\n')
        return (-1);
    count++;
    return (count);
}

int check_beginning_name(int count, general_t **general)
{
    for (; NAME_CMD_STRING[count] != '\0' &&
    (*general)->line[count] != '\0'; count++)
        if ((*general)->line[count] != NAME_CMD_STRING[count])
            return (-1);
    if ((*general)->line[count] == '\"')
        return (-1);
    for (; (*general)->line[count] != '\0' && ((*general)->line[count] == ' ' ||
    (*general)->line[count] == '\t'); count++);
    if ((*general)->line[count] != '\"')
        return (-1);
    if ((*general)->line[count + 1] == '\0' ||
    (*general)->line[count + 1] == '\n')
        return (-1);
    count++;
    return (count);
}

int check_end_name(int count, general_t **general, header_t **header)
{
    for (; (*general)->line[count] != '\0' &&
    (*general)->line[count] != COMMENT_CHAR &&
    (*general)->line[count] != '\n' && ((*general)->line[count] == ' ' ||
    (*general)->line[count] == '\t'); count++);
    if ((*general)->line[count] != '\0' &&
    (*general)->line[count] != COMMENT_CHAR && (*general)->line[count] != ' ' &&
    (*general)->line[count] != '\t' && (*general)->line[count] != '\n')
        return (84);
    if (check_comment(general, header) == 84)
        return (84);
    return (0);
}