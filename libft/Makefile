NAME=libft.a
CFLAGS=-Wall -Wextra -Werror
SRC=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_bzero.c \
	ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_toupper.c ft_tolower.c ft_strrchr.c \
	ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_strdup.c ft_strncmp.c \
	ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c
OBJS=$(SRC:.c=.o)
BONUS=ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	  ft_lstmap.c
OBJS_B=$(BONUS:.c=.o)
ifdef FLAG
	OBJ_TOTAL = $(OBJS) $(OBJS_B)
else
	OBJ_TOTAL = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJ_TOTAL)
	ar rcs $(NAME) $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -I.

bonus :
	make FLAG=1 all

clean :
	rm -f $(OBJS) $(OBJS_B)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean bonus re
