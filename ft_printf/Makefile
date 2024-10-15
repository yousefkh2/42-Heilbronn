# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c ft_putchar.c ft_putstr.c handle_char.c handle_hex.c handle_int.c handle_pointer.c handle_string.c handle_unsigned.c
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

# Rules
all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

test: all
	$(CC) $(CFLAGS) main.c libftprintf.a -o test_ft_printf

.PHONY: all clean fclean re test
