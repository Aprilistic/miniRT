# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 14:19:56 by jinheo            #+#    #+#              #
#    Updated: 2023/02/17 21:13:53 by taeypark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

SRCS	= main.c vec3/vec3_util.c vec3/vec3_util2.c
OBJS	= $(SRCS:.c=.o)
INCLUDES = includes/

CC		= cc
CFLAGS	= -Wall -Werror -Wextra
CLIB	= -Lmlx -lmlx -Imlx -framework OpenGL -framework Appkit

all		: $(NAME)

.c.o	:
		@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
		@echo "compiling libft..."
		@make all -s -C libft
		@echo "compiling mlx..."
		@make all -s -C mlx
		@echo "compiling all..."
		@$(CC) $(CFLAGS) $(CLIB) $(SRCS) libft/libft.a -I $(INCLUDES) -o $(NAME)
		@echo "done!"

clean	:
		@make clean -s -C mlx
		@make clean -s -C libft
		@rm -rf $(OBJS)
		@echo "erasing .o files"

fclean	: clean
		@rm -rf $(NAME)
		@echo "erasing executable"

bonus	: all

re		:
		@make fclean
		@make all

.PHONY	: all clean fclean re bonus
