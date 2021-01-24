/*
** EPITECH PROJECT, 2019
** CPE_corewar_2019
** File description:
** check_first_word.c
*/

int check_first_word(char *s1, char *s2)
{
    int m = 0;
    int i = 0;
    int first = 0;

    for (; s1[first] == '\t' || s1[first] == ' ' || s1[first] == '\n'; first++);
    while (s1[first] == s2[i] && s1[first] != '\0' && s2[i] != '\0') {
        first++;
        i++;
    }
    m = s1[first] - s2[i];
    if (s1[first] == ' ' && s2[i] == '\0')
        m = 0;
    return (m);
}