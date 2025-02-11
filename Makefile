# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 13:23:06 by ededemog          #+#    #+#              #
#    Updated: 2025/02/11 18:23:33 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d

SRCDIR := src/
OBJDIR := obj/
INCDIR := ./inc/mlx/ ./inc/mlx-mac/ ./inc/

LIBFT_PATH := ./inc/libft

SRC := $(SRCDIR)main.c \
       $(SRCDIR)parsing/read_map.c \
	   $(SRCDIR)utils/map_utils.c \

OBJ := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRC:.c=.o))

LIBFT := $(LIBFT_PATH)/libft.a 

ifeq ($(shell uname), Linux)
    INCLUDES = -I./inc/mlx -I./inc -I$(LIBFT_PATH)
    MLX := inc/mlx/libmlx_Linux.a
    MLX_FLAGS := -L./inc/mlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
    INCLUDES = -I./inc/mlx-mac -I./inc -I$(LIBFT_PATH)
    MLX := inc/mlx-mac/libmlx.a
    MLX_FLAGS := -L./inc/mlx-mac -lmlx -framework OpenGL -framework AppKit
endif

CC := cc
CFLAGS := -Wall -Wextra -Werror -g

RED := "\e[1;91m"
GREEN := "\e[1;92m"
RESET := "\e[0m"

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(dir $(OBJ))

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo $(GREEN)Compiling $< to $@$(RESET)

$(MLX):
	@make -sC inc/mlx/

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	@$(CC) $(OBJ) $(MLX_FLAGS) -L$(LIBFT_PATH) -lft -lm -o $(NAME)
	@echo $(GREEN)$(NAME) created!$(RESET)

clean:
	@rm -rf $(OBJDIR)
	@make -sC $(LIBFT_PATH) clean
	@echo $(RED)Objects cleaned!$(RESET)

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_PATH) fclean
	@echo $(RED)$(NAME) cleaned!$(RESET)

re: fclean all

.PHONY: all clean fclean re
