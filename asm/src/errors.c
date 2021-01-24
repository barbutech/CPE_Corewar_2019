/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** errors.c
*/

#include "../include/my.h"
#include "../../include/op.h"

int error_handling(int argc, char **argv)
{
    if (argc < 2) {
        write(2, "Usage: ./asm file_name[.s] ....\n", 32);
        return (84);
    }
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0) {
        write(1, "USAGE\n./asm file_name[.s]\nDESCRIPTION\nfile_name", 47);
        write(1, " file in assembly language to be converted into", 47);
        write(1, " file_name.cor, an executable in the Virtual Machine.\n", 54);
        return (0);
    }
    return (-1);
}

int check_comment(general_t **general, header_t **header)
{
    int count = 0;
    int length = 0;

    (*general) = (*general)->next;
    if ((count = check_beginning_comm(count, general)) <= 0) return (84);
    for (; (*general)->line[count] != '\0' &&
    (*general)->line[count] != '\"'; count++, length++) {
        if (length >= COMMENT_LENGTH)
            return (84);
        (*header)->comment[length] = (*general)->line[count];
    }
    (*header)->comment[length] = '\0';
    if ((*general)->line[count] != '\"')
        return (84);
    count++;
    return (check_end_comm(count, general));
}

int check_name_and_comment(general_t **general, header_t **header)
{
    int count = 0;
    int length = 0;

    (*general) = (*general)->head;
    if ((count = check_beginning_name(count, general)) <= 0)
        return (84);
    for (; (*general)->line[count] != '\0' &&
    (*general)->line[count] != '\"'; count++, length++) {
        if (length >= PROG_NAME_LENGTH)
            return (84);
        (*header)->prog_name[length] = (*general)->line[count];
    }
    (*header)->prog_name[length] = '\0';
    if ((*general)->line[count] != '\"')
        return (84);
    count++;
    return (check_end_name(count, general, header));
}

int search_lab(char *line, int *count, index_t **index)
{
    for (; line[(*count)] == '\0' ||
        line[(*count)] == '\t' || line[(*count)] == ' ' ||
        line[(*count)] == '\n'; (*count)++);
    for (int nbr = 0; op_tab[nbr].mnemonique != 0; nbr++)
        if (check_first_word(line, op_tab[nbr].mnemonique) == 0) return (0);
    if (index_this(index, count, line) == -1)
        return (-1);
    if (line[(*count)] != LABEL_CHAR || (line[(*count) + 1] != ' ' &&
    line[(*count) + 1] != '\t' && line[(*count) + 1] != '\n' &&
    line[(*count) + 1] != '\0'))
        return (-1);
    return (1);
}

int count_instruct(char *line)
{
    int count = 0;
    int nbr_of_instructs = 0;

    for (; line[count] == ' ' || line[count] == '\t'; count++);
    for (int nbr_sep = 0; line[count] != '\0' && line[count] != COMMENT_CHAR;) {
        for (; line[count] != ' ' && line[count] != '\t' &&
        line[count] != SEPARATOR_CHAR && line[count] != '\0' &&
        line[count] != COMMENT_CHAR; count++);
        if (line[count] == COMMENT_CHAR) return (nbr_of_instructs + 1);
        nbr_of_instructs++;
        for (; line[count] == ' ' || line[count] == '\t' ||
        line[count] == SEPARATOR_CHAR; count++)
            if (line[count] == SEPARATOR_CHAR) nbr_sep++;
        if (nbr_sep > 1)
            return (-1);
        nbr_sep = 0;
        if (line[count] == '\0')
            return (nbr_of_instructs);
    }
    return (nbr_of_instructs);
}