##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## make a file
##

SRC_ASM 	=	asm/src/main.c 		 	\
				asm/src/op.c 			\
				asm/src/errors.c 		\
				asm/src/my_strcmp.c 	\
				asm/src/linked_list.c 	\
				asm/src/my_strlen.c 	\
				asm/src/my_strdup.c 	\
				asm/src/paste.c 		\
				asm/src/checks_name_and_com.c 	\
				asm/src/check_first_word.c 	\
				asm/src/my_modified_getnbr.c 		\
				asm/src/params.c 					\
				asm/src/navigate.c 	\
				asm/src/others.c \

SRC_VM		=	corewar/src/main.c 		\

all:
		gcc -o asm/asm $(SRC_ASM) -g3 -Wall
		gcc -o corewar/corewar $(SRC_VM) -g3
clean:
		rm -rf $(OBJ)

test_run:
		gcc -o unit_test bonus/testcriterion.c $(SRC) -lcriterion
		./unit_test

fclean:		clean
		rm -rf asm/asm corewar/corewar

re:		fclean all
