NAME = fdf
SRCS = src/main.c src/render.c src/parser.c src/draw_map.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iminilibx-linux
MLX = minilibx-linux/libmlx.a -lX11 -lXext -lm
MLX_DIR = minilibx-linux
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
