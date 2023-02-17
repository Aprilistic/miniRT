# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 14:19:56 by jinheo            #+#    #+#              #
#    Updated: 2023/02/17 16:15:57 by taeypark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

SRCS	= main.c
OBJS	= $(SRCS:.c=.o)
INCLUDES = includes/

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
CLIB	= -Lmlx -lmlx -Imlx -framework OpenGL -framework Appkit

all		: $(NAME)

.c.o	:
		@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
		@echo "compiling..."
		@make all -s -C mlx
		@$(CC) $(CFLAGS) $(CLIB) $(SRCS) -I $(INCLUDES) -o $(NAME)
		@echo "done!"

clean	:
		@make clean -s -C mlx
		@rm -rf $(OBJS)
		@echo "erasing .o files"

fclean	: clean
		@rm -rf $(NAME)
		@echo "erasing .exec files"

bonus	: all

re		:
		@make fclean
		@make all

.PHONY	: all clean fclean re bonus
