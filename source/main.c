/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/24 14:36:56 by lesalmon         ###   ########.fr       */
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
		data->tab_token = ft_split_token(data->processed, data, 0, 0);
		data->token_lst = token_lst(data);
		data->parsing = sort_token(data, 1);
		pipex_setup(data, data->tab_token);
		free_all(data, command);
	}
}

int main (int argc, char **argv, char **envp)
{
	char	*command;
	t_data *data = malloc(sizeof(t_data));
	(void) argc;
	(void) argv;
	data = NULL;
	command = NULL;
	if (!envp)
		data = init_data(data, 1, envp);
	else
		data = init_data(data, 0, envp); // jai mis un int comme boolean pour savoir si on copi l'env en fonction de si on le donne a la compilation (1) pour non, (0) pour oui
	while (1)
	{
		command = readline("minishell> "); //fonction permettant de lire et garder en memoire l'entree utilisateur
		if (ft_strlen(command) >= 1)
		{
			if (syntax_are_closed(command))
			{
				add_history(command); //permet de garder dans l'historique
				a_out(data, command);
			}
		}
	}
}
