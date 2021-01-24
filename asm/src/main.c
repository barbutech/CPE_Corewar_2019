/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** main.c
*/

#include "../../include/op.h"
#include "../include/my.h"

int collect_file(char **argv, general_t **general)
{
    FILE *stream = fopen(argv[1], "r");
    char *line = NULL;
    size_t n = 0;

    if (stream == NULL)
        return (84);
    for (int ret = 0; (ret = getline(&line, &n, stream)) > 0;) {
        if (line[0] == '\n' || line[0] == '\0' || line[0] == COMMENT_CHAR)
            continue;
        stack_push(general, line);
    }
    free(line);
    fclose(stream);
    return (0);
}

int case_instruct(general_t *general, header_t *header, index_t *index)
{
    general = general->next;
    if (general == NULL)
        return (0);
    if (index)
        index = index->head;
    for (; general; general = general->next) {
        if ((general->nbr_instruct = count_instruct(general->line)) < 0)
            return (84);
        general->command = malloc(sizeof(int) * (general->nbr_instruct + 1));
        general->command[general->nbr_instruct] = -1;
        general->type = malloc(sizeof(int) * (general->nbr_instruct + 1));
        general->type[general->nbr_instruct] = -1;
        if (fill_int(&general, &index, &header) == 84)
            return (84);
    }
    return (0);
}

int main(int argc, char *argv[])
{
    int ret = 0;
    header_t *header = malloc(sizeof(header_t));
    header->prog_size = 0;
    general_t *general = NULL;
    index_t *index = NULL;

    if ((ret = error_handling(argc, argv)) >= 0) return (ret);
    if (collect_file(argv, &general) == 84) return (84);
    if (general == NULL) return (84);
    if (check_name_and_comment(&general, &header) == 84) return (84);
    if (case_labels(general, &index) == 84) return (84);
    if (case_instruct(general, header, index) == 84) return (84);
    if (turn_of_labels(general, index) == 84) return (84);
    if (copy_in_the_cor(argv, (*header), general) == 84) return (84);
    return 0;
}
