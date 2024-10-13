NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRCS = ft_printf.c \
       ft_putchar.c \
       ft_putstr.c \
       handle_char.c \
       handle_string.c \
       handle_pointer.c \
       handle_int.c \
       handle_unsigned.c \
       handle_hex.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I.

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
