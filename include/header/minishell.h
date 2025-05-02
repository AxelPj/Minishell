# ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

typedef struct s_data
{
	char **envp_cpy;

} s_data;
typedef struct t_lst
{
	
} t_lst;


//--------------Utils--------------//
void	init_data(s_data *data, int bool, char **envp);
void	envp_cpy(s_data *data, char **envp);

#endif