/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** my.h
*/

#include "structures.h"
#include "../../include/op.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

int error_handling(int argc, char **argv);
int check_name_and_comment(general_t **general, header_t **header);
int check_end_name(int count, general_t **general, header_t **header);
int check_beginning_name(int count, general_t **general);
int check_beginning_comm(int count, general_t **general);
int check_end_comm(int count, general_t **general);
int check_comment(general_t **general, header_t **header);

//libs

int my_strlen(char *str);
char *my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
int check_first_word(char *s1, char *s2);
int my_modified_getnbr(char *str, int *count);

// strucutres op

void stack_push(general_t **general, char *value);
int fill_int(general_t **general, index_t **index, header_t **header);
void index_label(index_t **index, general_t *general, int *count, int tempo);
int index_this(index_t **index, int *count, char *line);
int go_ahead(general_t *general, int tmp, int nbr_labels);
int go_back(general_t *general, int tmp, int nbr_labels);

//other

int copy_in_the_cor(char **argv, header_t header, general_t *general);

int search_lab(char *line, int *count, index_t **index);

int count_instruct(char *line);

int param_type(general_t *general, int count, int pos, header_t **header);

int pass_before_instructions(char *str, int count);

void header_to_big_endian(header_t *header);

int case_labels(general_t *general, index_t **index);

int value_label(general_t *general, index_t *index, int tmp);

int get_param_type(general_t *general, int count, header_t **header, int pos);

int turn_of_labels(general_t *general, index_t *index);

void convert_type(general_t *general, int count);

int is_a_label_here(general_t **general, int *count, int tmp, index_t **index);

int correct_byte(general_t **general, int pos, header_t **header);

int type_param(general_t **general, int type, int tmp, header_t **header);