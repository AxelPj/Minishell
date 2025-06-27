/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:22:25 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/24 17:32:34 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../GNL/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>

extern long	g_status;

enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_REDIRECT_APPEND,
	TOKEN_HEREDOC,
};

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
	t_pars	*parsing;
	char	**envp_cpy;
	char	**tab_token;
	int		nb_token;
	char	*processed;
	int		index_input;
}	t_data;

typedef struct s_exec
{
	int		nb_cmds;
	int		nb_args;
	char	**cmds;
	char	**envp;
	char	***tab_args;
	int		*fd;
	int		*infile; // <
	int		*here_doc; // <<
	char	**heredoc_lim; // >>
	char	**outfile; // >
	int		*out_flags; // 0_???
}	t_exec;

//---------------MAIN----------------//
//---------------SHELL_UTILS-------------//
void	set_shell(t_data *data);
void	sh_lvl(char **envp);
void	minishell(char *command, t_data	*data);
char	*search_sh_lvl(char **envp, int *j);
//--------------parsing--------------//
void	printtabb(char **tab);
void	print_data_lst(t_data *data);

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
int		token_type(char *s_token, int i);
t_pars	*sort_token(t_data *data, int i, int size);
int		count_token_word(int i, char **tab_token, int size);
char	*place_token(char *str, int start, int end);
int		count_token(char *processed, int i, int word);
char	**split_into_tokens(char *processed, t_data *data);
char	*find_end_token(char *processed, int *i);
void	skip_dq(char *processed, int *i);
void	skip_sq(char *processed, int *i);
void	skip_to_space_or_q(char *processed, int *i);
				//------expand------//
char	**split_into_expand(char *processed, t_data *data, int i, int j);
char	*find_end_dol_expand(char *s, int *start);
char	*find_end_word_split_expand(char *s, int *start);
int		count_word_split_expand(char *s, int i, int count_dol);
int		find_end_dq_to_expand(int *i, char *s, int count_dol);
void	find_end_word_split_dol(char *s, int *i);
t_pars	*process_expand(t_data *data, t_pars *parsing, int count_dol, int i);
char	**change_var_to_value(char **tab, int count_doll, int i);
char	*extract_var_name(char *s, int start);
char	*join_expand(char **tab, int size);
int		is_there_a_dol(char *s);
int		invalid_car_expand(char *s, int *i);
int		char_valid_dol(char s);
char	*dol_interog(char *s);
				//------clean_quote------//
t_pars	*clear_tab(t_data *data);
int		verif_clean_q(char *tab);
char	*clean_q(char *tab, int i, int j);
int		find_end_q(char *tab, int *i, char c, char d);
				//-------export_tab-----//
char	**extract_double_tab(char **tab, int size);
char	***import_tabs(t_data *data, t_exec *pipex, int count, int i);
//-----------------------------------//
//--------------Utils--------------//
int		verif_built_in(char *str);
void	print_lst(t_data *data);
t_data	*init_data(t_data *data, int bool, char **envp);
char	**envp_cpy(t_data *data, char **envp);
//--------------PRINTF_UTILS--------------//
void	print_pars_lst(t_data *data);
void	print_data_lst(t_data *data);
//------------lst---------------//
t_pars	*ft_lst_parsnw(char **s_tok, int type_tok, int *index, int size);
void	ft_pars_lstadd_bck(t_pars **lst, t_pars *new);
t_pars	*pars_lstlast(t_pars *lst);
int		ft_lst_pars_size(t_pars *lst);	
		//-----------free-----------//
void	free_all(t_data *data);
char	**free_tab(char **tab);
t_pars	*free_lst_pars(t_pars *parsing);
void	free_and_exit(t_data *data, t_exec *info, int bool);
void	free_partially(t_data *data, t_exec *info);
//---------------CHECK_BUILTINS--------------//
int		is_builtin_child(char *cmd);
int		is_builtin(char *cmd);
int		is_valid_builtin(char *cmd);
int		is_builtin_parent(char *cmd);
int		execute_builtin(char *cmd, char **args, t_exec *info, t_data *data);
//---------------COMMANDS---------//
int		command(t_exec *infos, char **envp, int i, t_data *data);
//---------------FREE_EXEC--------------//
void	free_split(char **tab);
void	free_info(t_exec *info);
void	free_tab_args(char ***cmds_args);
//---------------INIT_EXEC---------------//
t_exec	*init_infos(t_exec *info);
void	info_heredoc(t_exec *info);
//---------------MAIN_EXEC----------------//
void	set_last_status(int status);
void	launch_child(int i, t_exec *info, t_data *data);
int		exec_main(t_data *data, t_exec *info);
int		exec_setup(t_data *data, char **tab, t_exec *info);
//---------------EXEC_UTILS----------------//
void	count_nb(t_exec *info, char **tab, int i);
void	set_last_status(int status);
void	builtin_exec(t_exec *info, int idx, t_data *data);
//---------------PATH----------------//
char	*find_executable(char **paths, char *cmd);
char	*get_path_env(char **envp);
char	*cmd_path(char *cmd, char **envp);
//---------------PIPES---------------//
void	close_all_pipes(int *fd, int nb_pipes);
void	wait_all_children(int nb_cmds);
int		create_pipes(int *fd, int nb_pipes);
//---------------SETUP_FD----------------//
void	setup_input(int idx, t_exec *info);
//---------------REDIRECTION----------------//
char	**rm_redir(char **args);
void	setup_output(int idx, t_exec *info);
void	close_pipes(t_exec *info);
//--------------SETUP_REDIR-------------//
int		setup_here_doc(char *lim);
void	setup_redir(t_exec *info, char **arg);
//--------------REDIR_UTILS-------------//
void	heredoc(t_exec *info, char **args, int cmd, int i);
void	heredoc_limit(t_exec *info, char **args, int cmd, int i);
void	infile(t_exec *info, char **args, int cmd, int i);
void	outfile(t_exec *info, char **args, int cmd, int i);
//--------------BUILT-IN--------------//
int		ft_cd(char **input, t_data *data);
int		ft_echo(char **input, int fd);
int		check_n(char **input);
int		is_all_n(char *s);
int		ft_exit(char **args, t_exec *info, t_data *data, int bool);
int		ft_env(t_data *data);
int		ft_export(t_exec *info, t_data *data);
int		ft_pwd(t_data *data);
int		ft_unset(t_data *data, char *str);
//--------------EXPORT_UTILS--------------//
int		is_valid_varname(char *str);
int		var_exists(char **env, char *name);
void	update_var(char **env, int idx, char *str);
int		add_var(t_data *data, char *str);
//--------------GNL--------------//
char	*ft_readline(int fd, char *stach);
char	*recoveraftern(char *stach);
char	*recoverbeforen(char *line);
char	*get_next_line(int fd);

#endif
