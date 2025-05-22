/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/19 21:35:27 by lesalmon         ###   ########.fr       */
=======
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/21 20:41:03 by axel             ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../include/header/minishell.h"
void	a_out(s_data *data, char *command)
{
	if (command)
	{
		data->processed = space_to_input(data, command, 0);
		printf("%s\n", data->processed);
		write(1, "format input ok\n", 17);
		data->tab_token = ft_split_token(data->processed, data, 0, 0);
		write(1, "split ok\n", 10);
		data->token_lst = token_lst(data);
		write(1, "token ok\n", 10);
		print_lst(data);
		data->parsing = sort_token(data, 1, 0);
		print_pars_lst(data);
		free_all(data, command);
	}
}

int main (int argc, char **argv, char **envp)
{
	char	*command;
	s_data *data = malloc(sizeof(s_data));
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
		printf("command ok\n");
		if (ft_strlen(command) >= 1)
		{
			add_history(command); //permet de garder dans l'historique
			a_out(data, command);
		}
	}
}