NAME = fdf
SRCS = src/main.c src/parser.c src/render.c src/map.c src/utils.c src/events.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx_macos
MLX = -L ./minilibx_macos -lmlx -framework OPENGL -framework AppKit
MLX_DIR = minilibx_macos
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -L$(MLX_DIR) -I$(MLX_DIR) $(OBJS) -o $(NAME) $(MLX) $(LIBFT)


$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make clean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
