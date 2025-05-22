# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 14:45:18 by axelpeti          #+#    #+#              #
#    Updated: 2025/05/20 17:39:36 by lesalmon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = minishell

# Sources
SRCS =  source/main.c \
		source/utils/utils.c source/utils/init_data.c source/utils/split_modif.c source/utils/input_utils.c\
		source/tokenisation/format_input.c source/utils/env_utils.c\
		source/built-in/ft_cd.c source/built-in/ft_echo.c source/built-in/ft_env.c source/built-in/exit.c\
		source/built-in/export.c source/built-in/ft_pwd.c source/built-in/ft_unset.c\

# Répertoire et archive de la libft
LIBFT_DIR = ./include/libft
LIBFT = $(LIBFT_DIR)/libft.a

PIPEX_DIR = ./include/pipex
PIPEX = $(LIBFT_DIR)/pipex.a

# Répertoires
BUILD_DIR = build

# Fichiers objets
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Compilateur et options
CC = cc
CFLAGS = -Werror -Wextra -Wall -g #-ggdd
LDFLAGS = -lreadline

# Couleurs pour affichage
YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0m
RED = \033[0;31m

# Règle par défaut
all: $(LIBFT) $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS)
	@echo "$(YELLOW)🔨 Linking $(NAME)... 🚀$(RESET)"
	$(CC) $(OBJS) $(LIBFT) $(PIPEX) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful!$(RESET)"

# Compilation de la libft
$(LIBFT):
	@echo "$(YELLOW)🔨 Compiling libft... 🚀$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(PIPEX_DIR)

# Règle pour les fichiers objets, en créant les dossiers nécessaires
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)📝 Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(PIPEX_DIR) -c $< -o $@
	@echo "$(GREEN)✅ Compilation of $< finished$(RESET)"

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	rm -rf $(BUILD_DIR)
	@echo "$(RED)🧹 Cleaning libft objects...$(RESET)"
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(PIPEX_DIR)

# Nettoyage complet
fclean: clean
	@echo "$(RED)🧼 Removing executable...$(RESET)"
	rm -f $(NAME)
	@echo "$(RED)🧼 Cleaning libft archive...$(RESET)"
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(MAKE) fclean -C $(PIPEX_DIR)

# Recompilation complète
re: fclean all

# Mode debug
debug: CFLAGS += -g -fsanitize=address
debug: re

# Déclaration des cibles phony
.PHONY: all clean fclean re debug