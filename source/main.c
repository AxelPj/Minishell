/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/11 18:37:23 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header/minishell.h"

long	g_status = 0;

static void	sigint_parent(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

void	set_shell(t_data *data)
{
	int		i;

	i = 0;
	while (data->envp_cpy[i])
	{
		if (ft_strncmp(data->envp_cpy[i], "SHELL=", 6) == 0)
			data->envp_cpy[i] = ft_strdup("SHELL=minishell");
		i++;
	}
}
void	a_out(t_data *data, char *command)
{
	t_pipex	*info;
	
	info = malloc(sizeof(t_pipex));
	if (command)
	{
		data->processed = space_to_input(data, command, 0);
		data->tab_token = split_into_tokens(data->processed, data);
		data->token_lst = token_lst(data);
		data->parsing = sort_token(data, 1);
		data->parsing = process_expand(data, data->parsing, 0, 0);
		data->parsing = clear_tab(data);
		/* print_pars_lst(data);
		info->tab_args = import_tabs(data, info, ft_lst_pars_size(data->parsing), 0);
		pipex_setup(data, data->tab_token, info); */
		free_all(data, command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*command;
	t_data	*data;

	(void) argc;
	(void) argv;
	data = NULL;
	command = NULL;
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
	if (!envp)
		data = init_data(data, 1, envp);
	else
		data = init_data(data, 0, envp);
	while (1)
	{
		command = readline("minishell> ");
		if (ft_strlen(command) >= 1)
		{
			if (syntax_are_closed(command))
			{
				add_history(command);
				a_out(data, command);
			}
			else
			free (command);
		}
	}
	free (data);
}

/* void	printtabb(char **tab)
{
	int i;
	i = 0;
	while (tab[i])
	{
		printf ("tab = %s", tab[i]);
		i++;
	}
} */