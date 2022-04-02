# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anremiki <anremiki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 17:38:35 by anremiki          #+#    #+#              #
#    Updated: 2022/04/02 18:03:45 by anremiki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 

INCLUDES = ./includes/

OBJS = ${SRCS:.c=.o}

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -I $(INCLUDES) -lm

MLXFLAGS = ./minilibx/libmlx_Linux.a -lXext -lX11 -I ./minilibx/

NAME = cub3d

CC = gcc

NAMEEXIST = $(shell find . -name '$(NAME)' | wc -l)

TOTAL = $(shell find .srcs -name '*.c' | wc -l)

CURRENT = $(shell find .srcs -name '*.o' | wc -l | xargs expr 1 +)

COMPARE = $(shell expr $(TOTAL) + 1)

.c.o:
		@echo "Building $< $(CURRENT)/$(TOTAL)"
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME): $(OBJS)
		@echo
		@echo "\033[1;32mBuilding minilibx\033[0m"
		@echo
		@make -C ./minilibx
		@echo "\033[1;32Building libft\033[0m"
		@make -C ./libft
		@echo "\033[1;32mBuilding executable $(NAME)\033[0m"
		$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)

clean:
ifeq($(CURRENT), $(COMPARE))
		@echo "\033[1;33mClean $(NAME) objs\033[0m"
else
		@echo "\033[1;31m$(NAME) has no objs\033[0m"
endif
		$(RM) $(OBJS)
		@echo
		@echo "\033[1;33mClean minilibx\033[0m"
		make clean -C ./minilibx
		@echo
		@echo "\033[1;33mClean libft\033[0m"
		make clean -C ./libft

fclean: clean
ifeq($(NAMEEXIST), 1)
		@echo "033[1;33mClean $(NAME)\033[0m"
else
		@echo "\033[1;31m$(NAME) does not exist yet\033[0m"
endif
		@echo
		@echo "\033[1;33mClean mlx/.*a"
		$(RM) $(NAME)
		$(RM) ./minilibx/libmlx_Linux.a
		$(RM) ./minilibx/libmlx.a
		@echo
		@echo "\033[1;33mClean libft.a"
		make fclean -C ./libft

re:		fclean all

.PHONY: all clean fclean re

.SILENT: all clean fclean re
