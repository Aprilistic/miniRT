# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taeypark <taeypark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/13 14:19:56 by jinheo            #+#    #+#              #
#    Updated: 2023/02/23 16:52:43 by taeypark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= miniRT

SRCS	= main.c vec3/vec3_util.c vec3/vec3_util2.c our_mlx/our_mlx.c \
			parse/parse.c parse/parse_util.c parse/parse_util2.c parse/parse_util3.c \
			hit/hittable.c
OBJS	= $(SRCS:.c=.o)
INCLUDES = includes/

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -I.
CLIB	= -lmlx -Lmlx -framework OpenGL -framework Appkit


all		: $(NAME)

.c.o	:
		@$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	: $(OBJS)
		@echo "compiling libft..."
		@make all -s -C libft
		@echo "compiling mlx..."
		@make all -s -C mlx 2> /dev/null
		@echo "compiling all..."
		@$(CC) $(CFLAGS) $(CLIB) $(OBJS) libft/libft.a -o $(NAME)
		@echo "done!"

clean	:
		@make clean -s -C libft
		@make clean -s -C mlx
		@rm -rf $(OBJS)
		@echo "erasing .o files"

fclean	: clean
		@make fclean -s -C libft
		@rm -rf $(NAME)
		@echo "erasing executable"

bonus	: all

re		:
		@make fclean
		@make all

.PHONY	: all clean fclean re bonus
