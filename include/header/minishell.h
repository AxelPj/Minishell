/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:22:25 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 00:26:53 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

extern long	g_status;

enum	e_token_type
{
	TOKEN_WORD,
	TOKEN_BUILT_IN,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_DOLLAR,
	TOKEN_BACKTICK,
	TOKEN_UNKNOWN
}	;

typedef struct t_list
{
	char				**s;
	enum e_token_type	type;
	struct t_pars		*next;
}	t_list;

typedef struct s_data
{
	t_list	*parsing;
	char	**envp_cpy;
}	t_data;

typedef struct s_parsing
{
	char	**cmd;

}	t_parsing;

typedef struct s_pipex
{
	int		nb_cmds;
	char	**args;
	char	**cmds;
	char	**envp;
	int		*fd;
}	t_pipex;

//--------------tokenisation--------------//
int		is_one_delimiter(char c);
int		is_two_delimiter(char c, char c2);
int		count_len_input(char *input, int i, int len, int in_word);
char	*space_to_input(char *input, int len, int i, int j);

//--------------parsing--------------//
int		check_quote(char *str);

//--------------Utils--------------//
void	init_data(s_data *data, int bool, char **envp);
int		in_simple_quote(char c);
int		in_double_quote(char c);
int		verif_quote(char *processed, int i);
char	**envp_cpy(s_data *data, char **envp);
t_list	*ft_lstnw(int content);
void	ft_lstadd_bck(t_list **lst, t_list *new);
t_list	*lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
int		in_space(char c);
char	*place_token(const char *str, size_t start, size_t end);
int		count_token(char *processed, int i, int word);
char	**ft_split_token(char *s, int i, int j);
int		verif_built_in(char *command);

//--------------env_utils--------------//
char	*find_env(const char *name, char **envp);

//----------------PIPEX----------------//
int		pipex_mod(char **argv, char **envp);
int		command(char *cmd, char **envp);

//----------------PATH----------------//
char	*cmd_path(char *cmd, char **envp);
char	*find_path(char *path_env, char *cmd);
char	*copy_path(char *start, int len, char *cmd);
void	free_args(char **args);

//----------------PIPEX_UTILS---------//
int		create_pipes(int *fd, int nb_pipes);
void	dup_pipe(int i, t_pipex *info);
void	launch_child(int i, t_pipex *info);
void	close_all_pipes(int *fd, int nb_pipes);
void	wait_all_children(int nb_cmds);

//----------------UTILS3--------------//
int		is_valid_command(char *cmd);
int		is_valid_builtin(char *cmd);
void	is_valid(t_pipex *info, char **args);

//----------------SPLIT_PIPEX(UTILS2)-------//
char	**ft_split_pipex(char const *s, char c);

//--------------BUILT-IN--------------//
int		ft_cd(char **input, s_data *data);
int		ft_echo(char **input, int fd);
int		check_n(char **input);
int		is_all_n(char *s);
int		ft_env(s_data *data);
int		ft_export(s_data *data);
void	print_export(char **tab);
int		ft_pwd(void);
int		ft_unset(s_data *data, char *str);

#endif