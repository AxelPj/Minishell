/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/30 21:45:12 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header/minishell.h"

long	g_status = 0;

void	sigint_parent(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ctrl_d(t_data *data, t_exec *info)
{
	info->nb_args = 3;
	info->nb_cmds = 3;
	init_infos(info);
	ft_exit(NULL, info, data, 0);
}

void	a_out(t_data *data, char *command, t_exec *info, int size)
{
		data->processed = space_to_input(data, command, 0);
		free(command);
		command = NULL;
		data->tab_token = split_into_tokens(data->processed, data);
		free(data->processed);
		data->processed = NULL;
		size = tablen((void **)data->tab_token);
		data->parsing = sort_token(data, 0, size);
		data->parsing = process_expand(data, data->parsing, 0, 0);
		if (!data->parsing->tab_tok || !data->parsing->tab_tok[0])
		{
			data->parsing = free_lst_pars(data->parsing);
			free_all(data);
			return ;
		}
		data->parsing = clear_tab(data);
		info->tab_args = import_tabs(data, info,
				ft_lst_pars_size(data->parsing), 0);
		data->parsing = free_lst_pars(data->parsing);
		info->nb_args = 0;
		info->nb_cmds = 1;
		exec_setup(data, data->tab_token, info);
		free_all(data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*command;
	t_data	*data;

	data = NULL;
	command = NULL;
	signal(SIGINT, sigint_parent);
	signal(SIGQUIT, SIG_IGN);
	if (argc > 1 && !ft_strcmp(argv[1], "env") && !ft_strcmp(argv[2], "-i"))
	{
		envp = NULL;
		data = init_data(data, 1, envp);
	}
	else
		data = init_data(data, 0, envp);
	minishell(command, data);
	data->envp_cpy = free_tab(data->envp_cpy);
	free(data);
}

void	minishell(char *command, t_data	*data)
{
	t_exec	*info;

	info = malloc(sizeof(t_exec));
	while (1)
	{
		command = readline("OH MI(ni)SHELL> ");
		if (command == NULL)
			ctrl_d(data, info);
		if (ft_strlen(command) >= 1)
		{
			add_history(command);
			if (!syntax_are_closed(command))
				a_out(data, command, info, 0);
		}
		else
		{
			free(command);
			ft_putstr_fd("minishell : syntax error.\n", 2);
		}
	}
	free(info);
}
