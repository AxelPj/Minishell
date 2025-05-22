/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:22:25 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 14:21:21 by lesalmon         ###   ########.fr       */
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

enum e_token_type
{
	TOKEN_WORD,
	TOKEN_BUILT_IN,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
};

typedef struct t_list
{
	char				*s;
	enum e_token_type	token;
	int					index;
	struct t_list		*next;
}	t_list;

typedef struct t_pars
{
	char				**tab_tok;
	int					index;
	enum e_token_type	token;
	struct t_pars		*next;
}	t_pars;

typedef struct s_data
{
	t_list	*token_lst;
	t_pars	*parsing;
	char	**envp_cpy;
	char	**tab_token;
	int		nb_token;
	int		nb_pipe;
	char	*processed;
	int		index_input;
}	t_data;

typedef struct s_pipex
{
	int		nb_cmds;
	char	**args;
	char	**cmds;
	char	**envp;
	int		*fd;
}	t_pipex;

//--------------tokenisation--------------//
int		count_len_input(char *input, int i, int len, int in_word);
t_list	*token_lst(t_data *data);
int		token_type(char *s_token, int i);
char	*ft_tokenjoin(t_data *data, char *s1, char *s2, int start, int end);
char	*space_to_input(t_data *data, char *input, int i);
char	*ft_tokenquote(t_data *data, char *s1, char *s2, int start, int end);
int		verif_built_in(char *str);
t_pars	*sort_token(t_data *data, int i, int j);

//--------------parsing--------------//
void	print_lst(t_data *data);

//---------verif_synthaxique--------//
int		is_one_delimiter(char c);
int		is_two_delimiter(char c, char c2);
char	*process_del(t_data *data, char *input, char *processed, int i);
int		in_sq(char c);
int		in_dq(char c);
int		has_multi_q(char *input, int i);
char	*check_quote_or_delim(t_data *data, char *input, char *processed, int i);
int		in_quote_or_delim(char *input, int i);
char	*process_q(t_data *data, char *input, char *processed, int i, int start);
char	*process_multi_q(t_data *data, char *input, char *processed, int i, int start);
char	*process_del(t_data *data, char *input, char *processed, int i);
int		in_space(char c);
int		verif_quote(char *processed, int i);

//--------------Utils--------------//
t_data	*init_data(t_data *data, int bool, char **envp);
char	*ft_tokenjoin(t_data *data, char *s1, char *s2, int start, int end);
char	**envp_cpy(t_data *data, char **envp);
char	*place_token(const char *str, size_t start, size_t end);
int		count_token(char *processed, int i, int word);
char	**ft_split_token(char *processed, t_data *data, int i, int j);
void	print_pars_lst(t_data *data);

//------------lst---------------//
t_list	*ft_lstnw(int type_tok, char *tab_tok, int index);
void	ft_lstadd_bck(t_list **lst, t_list *new);
t_list	*lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
t_pars	*ft_lst_parsnw(char *s_tok, int type_tok, int index, int size);
void	ft_pars_lstadd_bck(t_pars **lst, t_pars *new);
t_pars	*pars_lstlast(t_pars *lst);
int		ft_lst_pars_size(t_pars *lst);

//-----------free-----------//
void	free_all(t_data *data, char *cmd);
void	free_tab(char **tab);
t_list	*free_token_lst(t_list *token_lst);
t_pars	*free_lst_pars(t_pars *parsing);

//----------------PIPEX----------------//
int		pipex_mod(t_data *data, char **argv);
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

//----------------UTILS1--------------//
int		execute_builtin(char *cmd, char **args, t_data *data);

//----------------SPLIT_PIPEX(UTILS2)-------//
char	**ft_split_pipex(char const *s, char c);

//----------------UTILS3--------------//
int		is_valid_command(char *cmd);
int		is_valid_builtin(char *cmd);
void	is_valid(t_pipex *info, char **args);
int		is_builtin_parent(char *cmd);
void	set_last_status(int status);

//--------------BUILT-IN--------------//
int		ft_cd(char **input, t_data *data);
int		ft_echo(char **input, int fd);
int		check_n(char **input);
int		is_all_n(char *s);
int		ft_exit(char **args);
int		ft_env(t_data *data);
int		ft_export(t_data *data);
void	print_export(char **tab);
int		ft_pwd(void);
int		ft_unset(t_data *data, char *str);

#endif