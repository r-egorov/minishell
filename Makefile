# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 12:47:19 by lelderbe          #+#    #+#              #
#    Updated: 2021/04/16 13:43:21 by cisis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLI_DIR		= cli/

CLICL_DIR	= ${CLI_DIR}cli_class/
CLICL_SRCS	= cli_readline.c
CLICL_SRCS	:= $(addprefix ${CLICL_DIR}, ${CLICL_SRCS})

LINE_DIR	= ${CLI_DIR}line_class/
LINE_SRCS	= line.c
LINE_SRCS	:= $(addprefix ${LINE_DIR}, ${LINE_SRCS})

MAIN_DIR	= main/
MAIN_SRCS	= main.c
MAIN_SRCS	:= $(addprefix ${MAIN_DIR}, ${MAIN_SRCS})

ERRORS_DIR	= errors/
ERRORS_SRCS	= process_errors.c
ERRORS_SRCS	:= $(addprefix ${ERRORS_DIR}, ${ERRORS_SRCS})


SRCS		= ${MAIN_SRCS} ${CLICL_SRCS} ${LINE_SRCS} ${ERRORS_SRCS}

#HEADERS		= minishell.h

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

LIBFT_DIR	= libft/

LIBFT		= libft.a

INCLUDES	= -I${LIBFT_DIR} -I${CLICL_DIR} -I${MAIN_DIR} -I${LINE_DIR} -I${ERRORS_DIR}

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c 
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
