/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:24:51 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 12:55:26 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>


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
	char			*s;
	enum			e_token_type token;
	int				index;
	struct t_list	*next;
} t_list;

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
	char    **tab_token;
	int		nb_token;
	int		nb_pipe;
	char	*processed;
	int     index_input;
} s_data;

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
s_data	*init_data(s_data *data, int bool, char **envp);
char	*ft_tokenjoin(s_data *data, char *s1, char *s2, int start, int end);
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
t_pars	*ft_lst_parsnw(char *s_tok, int type_tok, int index, int size);
void	ft_pars_lstadd_bck(t_pars **lst, t_pars *new);
t_pars	*pars_lstlast(t_pars *lst);
int		ft_lst_pars_size(t_pars *lst);

//-----------free-----------//
void	free_all(s_data *data, char *cmd);
void	free_tab(char **tab);
t_list	*free_token_lst(t_list *token_lst);
t_pars	*free_lst_pars(t_pars *parsing);

#endif