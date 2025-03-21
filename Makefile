# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 13:23:06 by ededemog          #+#    #+#              #
#    Updated: 2025/03/21 17:37:17 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := cub3D

SRCDIR := src/
OBJDIR := obj/
INCDIR := ./inc/mlx/ ./inc/mlx-mac/ ./inc/

LIBFT_PATH := ./inc/libft

SRC_FILES := main.c \
			map/validation/assets_validation.c \
			map/validation/colors_validation.c \
			parsing/map_parsing.c \
			parsing/parse_elements.c \
			parsing/textures_parsing.c \
			map/validation/validation.c \
			config/parse_config.c \
			config/process_config.c \
			init/init.c \
			init/init_all.c \
			init/init_textures.c \
			map/validation/map_bounds.c \
			map/validation/map_chars.c \
			map/validation/map_closed.c \
			map/validation/map_utils.c \
			map/validation/map_validation.c \
			map/player_init.c \
			map/doors.c \
			moves/handle_keys.c \
			moves/movements.c \
			moves/rotate.c \
			moves/mouse.c \
			moves/moves.c \
			rendering/render_map.c \
			rendering/raycasting.c \
			rendering/mini_map.c \
			rendering/raycasting_render.c \
			rendering/drawline.c \
			rendering/textures_test.c \
			utils/utils.c \
			utils/utils_2.c \
			utils/mini_map_utils.c \
			utils/raycasting_utils.c \
			utils/raycasting_utils_2.c \

SRC := $(addprefix $(SRCDIR), $(SRC_FILES))

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
CFLAGS := -Wall -Wextra -Werror -g -O3

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
