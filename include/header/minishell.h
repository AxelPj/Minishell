/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:22:25 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/02 17:32:55 by axelpeti         ###   ########.fr       */
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
# include <sys/wait.h>

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
	int					index_expand;
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
	int		nb_args;
	char	**cmds;
	char	**envp;
	char	***tab_args;
	int		*fd;
}	t_pipex;

//--------------parsing--------------//

		//------check_error_input------//
int		quotes_are_closed(char *s);
int		has_pipe_edges(char *s);
				//------syntax_utils------//
int		in_sq(char c);
int		in_dq(char c);
int		has_multi_q(char *input, int i);
int		is_one_delimiter(char c);
int		is_two_delimiter(char c, char c2);
int		verif_quote(char *processed, int i);
char	*process_syntax_symbol(t_data *data, char *input, int i);
int		in_syntax_symbol(char *input, int i);
int		in_open_braces(char c);
int		in_close_braces(char c);
int		braces_are_closed(char *s);
char	*process_braces(t_data *data, char *input, int i);
int		in_open_parens(char c);
int		in_close_parens(char c);
int		parens_are_closed(char *s);
char	*process_parens(t_data *data, char *input, int i);
int		in_open_brackets(char c);
int		in_close_brackets(char c);
int		brackets_are_closed(char *s);
char	*process_brackets(t_data *data, char *input, int i);
int		syntax_are_closed(char *command);
				//-----input_to_process-----//
char	*space_to_input(t_data *data, char *input, int i);
char	*process_q(t_data *data, char *input, int i, int start);
char	*process_multi_q(t_data *data, char *input, int i, int start);
void	multi_q_utils(t_data *data, char *input, int *pos, int *j);
char	*process_del(t_data *data, char *input, int i);
char	*process_join(t_data *data, char *s2, int start, int end);
char	*process_join_quote(t_data *data, char *s2, int start, int end);
				//------tokenisation------//
t_list	*token_lst(t_data *data);
int		token_type(char *s_token, int i);
int		count_non_delim(t_list *start);
t_pars	*non_delim_node(t_list *start, int idx);
t_pars	*delim_node(t_list *cur, int idx);
t_list	*process_non_delim(t_list *cur, t_data *data, int j);
t_list	*process_delim(t_list *cur, t_data *data, int j);
t_pars	*sort_token(t_data *data, int j);
char	*place_token(char *str, int start, int end);
int		count_token(char *processed, int i, int word);
char	**split_into_tokens(char *processed, t_data *data);
char	*find_end_token(char *processed, int *i);
void	skip_dq(char *processed, int *i);
void	skip_sq(char *processed, int *i);
void	skip_to_space_or_q(char *processed, int *i);
				//------expand------//
char	**split_into_expand(char *processed, t_data *data);
char	*find_end_word_to_expand(char *processed, int *i);
void	find_end_word_to_expand_utils(char *processed, int *pos);
void	skip_dq_for_expand(char *processed, int *i);
void	skip_after_dol_for_expand(char *processed, int *i);
void	skip_to_space_or_q_for_expand(char *processed, int *i);
int		count_word_to_expand(char *s, int i, int word);
char	*place_word_to_expand(const char *str, size_t start, size_t end);
void	process_expand(t_data *data, t_pars *parsing, int count_dol, int i);
char	**change_var_to_value(char **tab, int count_doll);
char	*extract_var_name(char *s);
int		count_dollars(char *s);
char	*join_expanded_tokens(char **tab);
void	skip_to_space_or_q_or_dol(char *processed, int *i);
void	skip_after_dol(char *processed, int *i);
				//------clean_quote------//
t_pars	*clear_tab(t_data *data);
int		verif_clean_q(char *tab);
char	*clean_q(char *tab);
int		find_end_q(char *tab, int *i, char c, char d);
                //-------export_tab-----//
char    **extract_double_tab(char **tab, int size);
char	***import_tabs(t_data *data, t_pipex *pipex, int count, int i);
//-----------------------------------//
				//--------------Utils--------------//
int		verif_built_in(char *str);
void	print_lst(t_data *data);
t_data	*init_data(t_data *data, int bool, char **envp);
char	**envp_cpy(t_data *data, char **envp);
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
char	**free_tab(char **tab);
t_list	*free_token_lst(t_list *token_lst);
t_pars	*free_lst_pars(t_pars *parsing);
//----------------PIPEX----------------//
int	pipex_setup(t_data *data, char **tab, t_pipex *info);
int		pipex_mod(t_data *data, t_pipex *info);
int		command(t_pipex *infos, char **envp, int i, t_data *data);
//----------------PATH----------------//
char	*cmd_path(char *cmd, char **envp);
char	*find_path(char *path_env, char *cmd);
char	*copy_path(char *start, int len, char *cmd);
void	free_args(char **args);
//----------------PIPEX_UTILS---------//
int		create_pipes(int *fd, int nb_pipes);
void	dup_pipe(int i, t_pipex *info);
void	launch_child(int i, t_pipex *info, t_data *data);
void	close_all_pipes(int *fd, int nb_pipes);
void	wait_all_children(int nb_cmds);

//----------------UTILS1--------------//
int		execute_builtin(char *cmd, char **args, t_pipex *info, t_data *data);
void	ft_tabfree(char **tab);
int		is_builtin_child(char *cmd);
int		is_builtin(char *cmd);
//----------------SPLIT_PIPEX(UTILS2)-------//
char	**ft_split_pipex(char const *s, char c);
//----------------UTILS3--------------//
int		is_valid_command(t_pipex *info, char *cmd);
int		is_valid_builtin(char *cmd);
void	is_valid(t_pipex *info, char **args);
int		is_builtin_parent(char *cmd);
void	set_last_status(int status);
//--------------BUILT-IN--------------//
int		ft_cd(char **input, t_pipex *info);
int		ft_echo(char **input, int fd);
int		check_n(char **input);
int		is_all_n(char *s);
int		ft_exit(char **args);
int		ft_env(t_data *data);
int		ft_export(t_pipex *info, t_data *data);
int		ft_pwd(void);
int		ft_unset(t_pipex *info, char *str);
//--------------EXPORT_UTILS--------------//
int		is_valid_varname(char *str);
int		var_exists(char **env, char *name);
void	update_var(char **env, int idx, char *str);
int		add_var(t_data *data, char *str);
//--------------------MAIN---------------//
void	set_shell(t_data *data);
//--------------TAB_ARGS---------------//
void	free_tab_args(char ***cmds_args);
char	***tab_args(char **tab);

#endif
