#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

typedef struct t_list
{
	char			*s;
	int				token;
	struct t_list	*next;
} t_list;

typedef struct s_data
{
	t_list	*list;
	char	**envp_cpy;

} s_data;

/* typedef struct t_parsing
{
	char **cmd;

} s_parsing; */

/*

ls -la | rev | wc -l

*/

//--------------tokenisation--------------//
int		is_one_delimiter(char c);
char	*space_to_input(char *input, int len, int i, int j);
int	skip_space(char c, char c2);

//--------------parsing--------------//
int		check_quote(char *str);

//--------------Utils--------------//
void	init_data(s_data *data, int bool, char **envp);
char	**envp_cpy(s_data *data, char **envp);
t_list	*ft_lstnw(int content);
void	ft_lstadd_bck(t_list **lst, t_list *new);
t_list	*lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);

#endif