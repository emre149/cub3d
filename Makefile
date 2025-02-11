# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 13:23:06 by ededemog          #+#    #+#              #
#    Updated: 2025/02/11 16:11:12 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/07 13:23:06 by ededemog          #+#    #+#              #
#    Updated: 2025/02/11 19:30:00 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME := cub3d

# Dossiers
SRCDIR := src/
OBJDIR := obj/
INCDIR := ./inc/mlx/ ./inc/mlx-mac/ ./inc/

# Dossier Libft
LIBFT_PATH := ./inc/libft

# Liste des fichiers sources
SRC := $(SRCDIR)main.c \
       $(SRCDIR)parsing/read_map.c \
	   $(SRCDIR)utils/map_utils.c \

# Générer les fichiers objets correspondants
OBJ := $(patsubst $(SRCDIR)%, $(OBJDIR)%, $(SRC:.c=.o))

# Libft et MiniLibX
LIBFT := $(LIBFT_PATH)/libft.a 

# Détection du système (Linux ou macOS)
ifeq ($(shell uname), Linux)
    INCLUDES = -I./inc/mlx -I./inc -I$(LIBFT_PATH)
    MLX := inc/mlx/libmlx_Linux.a
    MLX_FLAGS := -L./inc/mlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
    INCLUDES = -I./inc/mlx-mac -I./inc -I$(LIBFT_PATH)
    MLX := inc/mlx-mac/libmlx.a
    MLX_FLAGS := -L./inc/mlx-mac -lmlx -framework OpenGL -framework AppKit
endif

# Compilateur et flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -g

# Couleurs pour les logs
RED := "\e[1;91m"
GREEN := "\e[1;92m"
RESET := "\e[0m"

# Règle principale
all: $(OBJDIR) $(NAME)

# Création du dossier obj/
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(dir $(OBJ))

# Compilation des fichiers .c en .o
$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo $(GREEN)Compiling $< to $@$(RESET)

# Compilation de la MiniLibX
$(MLX):
	@make -sC inc/mlx/

# Compilation de Libft
$(LIBFT):
	@make -sC $(LIBFT_PATH)

# Compilation finale
$(NAME): $(OBJ) $(MLX) $(LIBFT)
	@$(CC) $(OBJ) $(MLX_FLAGS) -L$(LIBFT_PATH) -lft -lm -o $(NAME)
	@echo $(GREEN)$(NAME) created!$(RESET)

# Nettoyage des objets
clean:
	@rm -rf $(OBJDIR)
	@make -sC $(LIBFT_PATH) clean
	@echo $(RED)Objects cleaned!$(RESET)

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_PATH) fclean
	@echo $(RED)$(NAME) cleaned!$(RESET)

# Recompilation complète
re: fclean all

# Ne pas considérer ces noms comme des fichiers
.PHONY: all clean fclean re
