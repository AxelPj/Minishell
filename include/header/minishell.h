/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:22:25 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 00:26:53 by lesalmon         ###   ########.fr       */
=======
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:24:51 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 12:55:26 by axel             ###   ########.fr       */
>>>>>>> origin/main
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
<<<<<<< HEAD
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
=======
	TOKEN_HEREDOC,
};

typedef struct t_list
{
	char			*s;
	enum			e_token_type token;
	int				index;
	struct t_list	*next;
} t_list;
>>>>>>> origin/main

typedef struct t_pars
{
	char			**tab_tok;
	int				index;
	enum			e_token_type token;
	struct t_pars	*next;
} t_pars;

typedef struct s_data
{
	t_list	*token_lst;
 	t_pars	*parsing;
	char	**envp_cpy;
<<<<<<< HEAD
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

=======
	char    **tab_token;
	int		nb_token;
	int		nb_pipe;
	char	*processed;
	int     index_input;
} s_data;

>>>>>>> origin/main
//--------------tokenisation--------------//
int		count_len_input(char *input, int i, int len, int in_word);
t_list	*token_lst(s_data *data);
int		token_type(char *s_token, int i);
char	*ft_tokenjoin(s_data *data, char *s1, char *s2, int start, int end);
char	*space_to_input(s_data *data, char *input, int i);
char	*ft_tokenquote(s_data *data, char *s1, char *s2, int start, int end);
int		verif_built_in(char *str);
t_pars	*sort_token(s_data *data, int i, int j);

//--------------parsing--------------//
void	print_lst(s_data *data);

//---------verif_synthaxique--------//
int		is_one_delimiter(char c);
int		is_two_delimiter(char c, char c2);
char	*process_del(s_data *data, char *input, char *processed, int i);
int     in_sq(char c);
int     in_dq(char c);
int		has_multi_q(char *input, int i);
char	*check_quote_or_delim(s_data *data, char *input, char *processed, int i);
int		in_quote_or_delim(char *input, int i);
char	*process_q(s_data *data, char *input, char *processed, int i, int start);
char	*process_multi_q(s_data *data, char *input, char *processed, int i, int start);
char	*process_del(s_data *data, char *input, char *processed, int i);
int     in_space (char c);
int     verif_quote(char *processed, int i);

//--------------Utils--------------//
<<<<<<< HEAD
void	init_data(s_data *data, int bool, char **envp);
int		in_simple_quote(char c);
int		in_double_quote(char c);
int		verif_quote(char *processed, int i);
=======
s_data	*init_data(s_data *data, int bool, char **envp);
char	*ft_tokenjoin(s_data *data, char *s1, char *s2, int start, int end);
>>>>>>> origin/main
char	**envp_cpy(s_data *data, char **envp);
char	*place_token(const char *str, size_t start, size_t end);
int     count_token(char *processed, int i, int word);
char	**ft_split_token(char *processed, s_data *data, int i, int j);
void	print_pars_lst(s_data *data);

//------------lst---------------//
t_list	*ft_lstnw(int type_tok, char *tab_tok, int index);
void	ft_lstadd_bck(t_list **lst, t_list *new);
t_list	*lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
<<<<<<< HEAD
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
=======
t_pars	*ft_lst_parsnw(char *s_tok, int type_tok, int index, int size);
void	ft_pars_lstadd_bck(t_pars **lst, t_pars *new);
t_pars	*pars_lstlast(t_pars *lst);
int		ft_lst_pars_size(t_pars *lst);

//-----------free-----------//
void	free_all(s_data *data, char *cmd);
void	free_tab(char **tab);
t_list	*free_token_lst(t_list *token_lst);
t_pars	*free_lst_pars(t_pars *parsing);
>>>>>>> origin/main

#endif