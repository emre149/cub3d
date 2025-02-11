# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 15:53:33 by ededemog          #+#    #+#              #
#    Updated: 2025/02/11 16:11:58 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
EXEC = prog
SRCS = basics/ft_atoi.c basics/ft_isalnum.c basics/ft_isalpha.c \
		basics/ft_isascii.c basics/ft_isdigit.c basics/ft_isspace.c \
        basics/ft_isprint.c string/ft_strchr.c string/ft_strrchr.c \
		string/ft_strlen.c basics/ft_tolower.c \
        basics/ft_toupper.c string/ft_strdup.c basics/ft_putchar_fd.c \
		basics/ft_putstr_fd.c basics/ft_putendl_fd.c string/ft_strlcpy.c \
		memory/ft_bzero.c memory/ft_memset.c memory/ft_memcpy.c \
        basics/ft_putnbr_fd.c memory/ft_memmove.c string/ft_strnstr.c \
		string/ft_strlcat.c memory/ft_calloc.c string/ft_strncmp.c \
		string/ft_strmapi.c memory/ft_memchr.c memory/ft_memcmp.c \
		string/ft_substr.c string/ft_striteri.c string/ft_itoa.c \
		string/ft_strjoin.c string/ft_split.c string/ft_strtrim.c \
        maths/ft_atoll.c maths/ft_fibonnaci.c list/ft_lstnew.c \
		list/ft_lstadd_front.c list/ft_lstsize.c list/ft_lstlast.c \
		list/ft_lstadd_back.c list/ft_lstdelone.c list/ft_lstclear.c \
		list/ft_lstiter.c list/ft_lstmap.c gnl/get_next_line.c \
		gnl/get_next_line_utils.c memory/ft_realloc.c \
		memory/ft_memdel.c

MAIN	=	main.c

OBJM	=	$(MAIN:.c=.o)

TNAME	= 	test

OBJS 	= 	$(SRCS:.c=.o)

AR		= 	ar rc

RM		= 	rm -f

.c.o:
	@echo "🔨 Compiling $<..."
	@$(CC) $(CFLAGS) -o $(<:.c=.o) -c $<

$(NAME):	$(OBJS)
	@echo "📦 Creating archive $(NAME)..."
	@$(AR) $(NAME) $(OBJS)
	@echo "✅ Archive $(NAME) created!"

test:		$(NAME) bonus
	@echo "🚀 Building test executable..."
	@$(CC) $(CFLAGS) -o $(TNAME) $(MAIN) -L. -lft
	@echo "✅ Test executable $(TNAME) created!"

ifneq ($(shell uname), Darwin)
breaker:
	@echo "🔧 Building shared library for Linux..."
	@$(CC) -nostartfiles -shared -fPIC -ldl $(CFLAGS) -o libft.so $(SRCS) $(BONUS)
	@echo "✅ Shared library libft.so created!"
else
breaker:
	@echo "🔧 Building shared library for macOS..."
	@$(CC) -dynamiclib $(CFLAGS) -o libft.so $(SRCS) $(BONUS) -L../obj -lmalloc
	@echo "✅ Shared library libft.so created!"
endif

all:		$(NAME)

bonus:		$(OBJB)
	@echo "🔨 Compiling bonus files..."
	@$(AR) $(NAME) $(OBJB)
	@echo "✅ Bonus files compiled and added to $(NAME)!"

clean:
	@echo "🧹 Cleaning object files..."
	@$(RM) $(OBJS) $(OBJM) $(OBJB)
	@echo "✅ Object files cleaned!"

fclean:		clean
	@echo "🧹 Cleaning all generated files..."
	@$(RM) $(NAME) $(TNAME)
	@echo "✅ All generated files cleaned!"

re:			fclean all

.PHONY:		all clean fclean re test