/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** paste.c
*/

#include "../include/my.h"
#include "../../include/op.h"

char *cut_and_paste(char *argv)
{
    int count = my_strlen(argv);
    char *file = my_strdup(argv);
    if (argv[count - 1] != 's')
        return (NULL);
    file = realloc(file, count + 3);
    file[count - 1] = 'c';
    file[count] = 'o';
    file[count + 1] = 'r';
    file[count + 2] = '\0';
    return (file);
}

void write_in_file(int fd, general_t *general)
{
    if (general->is_label == 1)
        return ;
    write(fd, &general->command[0], general->type[0]);
    if (general->coding_byte != 0)
        write(fd, &general->coding_byte, 1);
    for (int count = 1; general->command[count] != -1; count++) {
        convert_type(general, count);
        write(fd, &general->command[count], general->type[count]);
    }
}

int copy_in_the_cor(char **argv, header_t header, general_t *general)
{
    char *file = cut_and_paste(argv[1]);
    if (file == NULL)
        return (84);
    header_to_big_endian(&header);

    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
        return (84);
    write(fd, &header, sizeof(header_t));
    for (general = general->next; general; general = general->next)
        write_in_file(fd, general);
    close(fd);
    return (0);
}

int copy_inst(general_t **general, index_t **index, int pos, header_t **header)
{
    int count = pass_before_instructions((*general)->line, 0);

    for (int tmp = 1, type = 0; tmp < (*general)->nbr_instruct; tmp++) {
        for (; (*general)->line[count] == ' ' ||
        (*general)->line[count] == '\t' ||
        (*general)->line[count] == SEPARATOR_CHAR; count++);
        type = param_type((*general), count, tmp, header);
        if ((op_tab[pos].type[tmp - 1] & type) == 0)
            return (84);
        if (is_a_label_here(general, &count, tmp, index) == 84) return (84);
        if (type_param(general, type, tmp, header) == 84) return (84);
    }
    return (correct_byte(general, pos, header));
}

int fill_int(general_t **general, index_t **index, header_t **header)
{
    int count = 0;
    (*general)->coding_byte = 0;

    if ((*general)->is_label == 1) {
        (*index)->next ? (*index) = (*index)->next : 0;
        return (0);
    }
    while (check_first_word((*general)->line, op_tab[count].mnemonique) != 0)
        count++;
    if (((*general)->nbr_instruct - 1) != op_tab[count].nbr_args ||
    ((*general)->nbr_instruct - 1) > MAX_ARGS_NUMBER)
        return (84);
    (*general)->command[0] = op_tab[count].code;
    (*general)->type[0] = 1;
    (*header)->prog_size++;
    (*general)->line_size++;
    if (copy_inst(general, index, count, header) == 84)
        return (84);
    return (0);
}