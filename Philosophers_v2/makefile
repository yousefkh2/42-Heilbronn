# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: YourName <your.email@example.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: YYYY/MM/DD HH:MM:SS by YourName          #+#    #+#              #
#    Updated: YYYY/MM/DD HH:MM:SS by YourName         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------ Compiler Settings ---------------------------- #

# Compiler to use
CC = gcc

# Compiler flags:
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -Werror: Treat warnings as errors
# -pthread: Enable POSIX threads
CFLAGS = -Wall -Wextra -Werror -pthread

# Optional: Add debugging symbols
# CFLAGS += -g

# ------------------------------- Project Files ------------------------------ #

# Source files
SRC = init.c main.c monitor.c philosopher.c utils.c queue.c

# Object files (replace .c with .o)
OBJ = $(SRC:.c=.o)

# Header files
HEADERS = philosophers.h

# Executable name
NAME = philo

# ------------------------------- Make Targets ------------------------------- #

# Default target: Build the executable
all: $(NAME)

# Link object files to create the executable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Compile .c files to .o files
# This pattern rule ensures that only changed .c files are recompiled
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: Remove object files
clean:
	rm -f $(OBJ)

# Full clean: Remove object files and the executable
fclean: clean
	rm -f $(NAME)

# Rebuild: Perform a full clean and then build again
re: fclean all

# Phony targets: Prevent conflicts with files named 'all', 'clean', etc.
.PHONY: all clean fclean re
