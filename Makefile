# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 13:23:06 by ededemog          #+#    #+#              #
#    Updated: 2025/02/07 13:23:09 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3d

SRCDIR := src/
OBJDIR := obj/
INCDIR := ./inc/mlx/ \
		./inc/mlx-mac/ \
		./inc/
LIBFT_PATH := ./inc/libft 

SRC := main.c
OBJ := $(SRC:.c=.o)

SRC := $(addprefix $(SRCDIR),$(SRC))
OBJ := $(addprefix $(OBJDIR),$(OBJ))

LIBFT := $(LIBFT_PATH)/libft.a 

RED := "\e[1;91m"
GREEN := "\e[1;92m"
RESET := "\e[0m"

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
CFLAGS := -Werror -Wextra -Wall -g

all: $(OBJDIR) $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo $(GREEN)Compiling $< to $@$(RESET)

$(MLX):
	@make -sC inc/mlx/

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

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