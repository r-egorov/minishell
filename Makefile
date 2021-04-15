# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 12:47:19 by lelderbe          #+#    #+#              #
#    Updated: 2021/04/15 13:08:15 by cisis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLI_DIR		= cli/
CLI_SRCS	= cli_readline.c
CLI_SRCS	:= $(addprefix $(CLI_DIR), $(CLI_SRCS))

LINE_DIR	= $(CLI_DIR)line_class/
LINE_SRCS	= line.c
LINE_SRCS	:= $(addprefix $(LINE_DIR), $(LINE_SRCS))

MAIN_DIR	= main/
MAIN_SRCS	= main.c		process_errors.c
MAIN_SRCS	:= $(addprefix $(MAIN_DIR), $(MAIN_SRCS))


SRCS		= ${MAIN_SRCS} ${CLI_SRCS} ${LINE_SRCS}

HEADERS		= minishell.h

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

LIBFT_DIR	= libft/

LIBFT		= libft.a

INCLUDES	= -I${LIBFT_DIR} -I${CLI_DIR} -I${MAIN_DIR} -I${LINE_DIR}

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${LIBFT_DIR}${LIBFT} ${OBJS}
			${CC} ${OBJS} ${INCLUDES} -L${LIBFT_DIR} -lft ${MLXFLAGS} -o ${NAME} -ltermcap

debug:		${LIBFT_DIR}${LIBFT} ${OBJS}
			${CC} -g ${OBJS} ${INCLUDES} -L${LIBFT_DIR} -lft ${MLXFLAGS} -o ${NAME} -ltermcap

${LIBFT_DIR}${LIBFT}:	${LIBFT_DIR}
			${MAKE} -C ${LIBFT_DIR} bonus

bonus:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ${LIBFT_DIR} clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C ${LIBFT_DIR} fclean
#			cd libft && ${MAKE} fclean

re:			fclean all

.PHONY:		all clean fclean re
