# Nom de l'exécutable
NAME = minishell

# Sources
SRCS =  source/main.c \
		source/parsing/syntax_utils/delimiteur_utils.c source/parsing/syntax_utils/quote_utils.c source/parsing/syntax_utils/pipe_utils.c source/parsing/syntax_utils/redir_utils.c source/parsing/syntax_utils/braces_utils.c source/parsing/syntax_utils/parens_utils.c source/parsing/syntax_utils/brackets_utils.c \
		source/parsing/input/input_normalizer.c source/parsing/input/input_processor.c \
		source/parsing/tokenisation/split_modif.c source/parsing/tokenisation/tokenisation.c \
		source/parsing/expand/expand_var.c source/parsing/expand/valid_expand.c source/parsing/expand/split_expand.c source/parsing/expand/expand_utils.c \
		source/parsing/delete_quote/del_q.c source/parsing/tokenisation/split_modif_utils.c \
		source/parsing/export_in_tab/export_in_tab.c source/utils/utils.c source/utils/free.c \
		source/utils/init_data.c source/utils/utils_lst.c \
		source/built-in/my_cd.c source/built-in/my_echo.c source/built-in/my_env.c source/built-in/my_exit.c source/built-in/shell_utils.c \
		source/built-in/my_export.c source/built-in/export_utils.c source/built-in/my_pwd.c source/built-in/my_unset.c source/built-in/cd_utils.c \
		source/exec/check_builtins.c source/exec/commands.c source/exec/free_exec.c source/exec/init_exec.c source/exec/main_exec.c source/exec/path.c \
		source/exec/pipes.c source/exec/exec_utils.c source/exec/setup_fd.c \
		source/redirections/redirection.c source/redirections/setup_redir.c \
		source/redirections/redir_utils.c \
		include/GNL/get_next_line.c \

# Répertoire et archive de la libmy
LIBMY_DIR = ./include/libmy
LIBMY = $(LIBMY_DIR)/libmy.a

# Répertoires
BUILD_DIR = build

# Fichiers objets
OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

# Compilateur et options
CC = cc
CFLAGS   = -Wall -Wextra -Werror -g -fPIE
CPPFLAGS = -Iinclude/header -I$(LIBMY_DIR)
LDFLAGS = -lreadline

# Sous macOS, le readline du système (libedit) ne fournit pas rl_replace_line :
# on utilise GNU readline installé avec Homebrew (brew install readline).
ifeq ($(shell uname), Darwin)
	READLINE_DIR := $(shell brew --prefix readline 2>/dev/null)
	ifneq ($(READLINE_DIR),)
		CPPFLAGS += -I$(READLINE_DIR)/include
		LDFLAGS := -L$(READLINE_DIR)/lib $(LDFLAGS)
	endif
endif

# Couleurs pour affichage
YELLOW = \033[0;33m
GREEN = \033[0;32m
RESET = \033[0m
RED = \033[0;31m

# Règle par défaut
all: $(LIBMY) $(NAME)

# Compilation de l'exécutable
$(NAME): $(OBJS) $(LIBMY)
	@echo "$(YELLOW)🔨 Linking $(NAME)... 🚀$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBMY) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Compilation successful!$(RESET)"

# Compilation de la libmy
$(LIBMY): $(wildcard $(LIBMY_DIR)/*.c) $(LIBMY_DIR)/libmy.h
	@echo "$(YELLOW)🔨 Compiling libmy... 🚀$(RESET)"
	$(MAKE) -C $(LIBMY_DIR)

# Règle pour les fichiers objets, en créant les dossiers nécessaires
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)📝 Compiling $<...$(RESET)"
	@echo "$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)✅ Compilation of $< finished$(RESET)"

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	rm -rf $(BUILD_DIR)
	@echo "$(RED)🧹 Cleaning libmy objects...$(RESET)"
	$(MAKE) clean -C $(LIBMY_DIR)

# Nettoyage complet
fclean: clean
	@echo "$(RED)🧼 Removing executable...$(RESET)"
	rm -f $(NAME)
	@echo "$(RED)🧼 Cleaning libmy archive...$(RESET)"
	$(MAKE) fclean -C $(LIBMY_DIR)

# Recompilation complète
re: fclean all

# Mode debug
debug: CFLAGS += -g -fsanitize=address
debug: re

.PHONY: all clean fclean re debug
