/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/29 16:29:46 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header/minishell.h"

long	g_status = 0;

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
	if (command)
	{
		data->processed = space_to_input(data, command, 0);
		data->tab_token = split_into_tokens(data->processed, data);
		data->token_lst = token_lst(data);
		data->parsing = sort_token(data, 1);
		process_expand(data, data->parsing, 0, 0);
		data->parsing = clear_tab(data);
		print_pars_lst(data);
		pipex_setup(data, data->tab_token);
		free_all(data, command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*command;
	t_data	*data;

	data = malloc(sizeof(t_data));
	(void) argc;
	(void) argv;
	data = NULL;
	command = NULL;
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
		}
	}
}
