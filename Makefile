# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 14:45:18 by axelpeti          #+#    #+#              #
#    Updated: 2025/06/27 21:47:51 by lesalmon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = minishell

# Sources
SRCS =  source/main.c \
		source/parsing/syntax_utils/delimiteur_utils.c source/parsing/syntax_utils/quote_utils.c source/parsing/syntax_utils/braces_utils.c source/parsing/syntax_utils/parens_utils.c source/parsing/syntax_utils/brackets_utils.c \
		source/parsing/input/input_normalizer.c source/parsing/input/input_processor.c \
		source/parsing/tokenisation/split_modif.c source/parsing/tokenisation/tokenisation.c \
		source/parsing/expand/expand_var.c source/parsing/expand/valid_expand.c source/parsing/expand/split_expand.c \
		source/parsing/delete_quote/del_q.c source/parsing/tokenisation/split_modif_utils.c \
		source/parsing/export_in_tab/export_in_tab.c source/utils/utils.c source/utils/free.c \
		source/utils/init_data.c source/utils/utils_lst.c \
		source/built-in/ft_cd.c source/built-in/ft_echo.c source/built-in/ft_env.c source/built-in/ft_exit.c source/built-in/shell_utils.c \
		source/built-in/ft_export.c source/built-in/export_utils.c source/built-in/ft_pwd.c source/built-in/ft_unset.c source/built-in/cd_utils.c\
		source/exec/check_builtins.c source/exec/commands.c source/exec/free_exec.c source/exec/init_exec.c source/exec/main_exec.c source/exec/path.c \
		source/exec/pipes.c source/exec/exec_utils.c source/exec/setup_fd.c\
		source/redirections/redirection.c source/redirections/setup_redir.c \
		source/redirections/redir_utils.c \
		include/GNL/get_next_line.c \

# Répertoire et archive de la libft
LIBFT_DIR = ./include/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Répertoires
BUILD_DIR = build

# Fichiers objets
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Compilateur et options
CC = cc
CFLAGS   = -Wall -Wextra -Werror -g -fPIE
CPPFLAGS = -Iinclude/header -I$(LIBFT_DIR)
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
	$(CC) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful!$(RESET)"

# Compilation de la libft
$(LIBFT):
	@echo "$(YELLOW)🔨 Compiling libft... 🚀$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)

# Règle pour les fichiers objets, en créant les dossiers nécessaires
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)📝 Compiling $<...$(RESET)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compilation of $< finished$(RESET)"

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	rm -rf $(BUILD_DIR)
	@echo "$(RED)🧹 Cleaning libft objects...$(RESET)"
	$(MAKE) clean -C $(LIBFT_DIR)

# Nettoyage complet
fclean: clean
	@echo "$(RED)🧼 Removing executable...$(RESET)"
	rm -f $(NAME)
	@echo "$(RED)🧼 Cleaning libft archive...$(RESET)"
	$(MAKE) fclean -C $(LIBFT_DIR)

# Recompilation complète
re: fclean all

# Mode debug
debug: CFLAGS += -g -fsanitize=address
debug: re

.PHONY: all clean fclean re debug
