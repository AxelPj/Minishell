/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/04 15:12:20 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header/minishell.h"

int main (int argc, char **argv, char **envp)
{
	char	*command;
	s_data	*data;
	char	*after_cmd;
	char **tab;	
	(void) argc;
	(void) argv;
	data = NULL;
	if (!envp)
		init_data(data, 1, envp);
	else
		init_data(data, 0, envp); // jai mis un int comme boolean pour savoir si on copi l'env en fonction de si on le donne a la compilation (1) pour non, (0) pour oui
	while (1)
	{
		command = readline("minishell> "); //fonction permettant de lire et garder en memoire l'entree utilisateur
		add_history(command); //permet de garder dans l'historique
		after_cmd = space_to_input(command, ft_strlen(command), 0, 0);
		printf("\n\n%s\n\n", after_cmd);
		tab = ft_split_token(after_cmd, 0, 0);
		printf("%s", tab[0]);
		free(command); //liberer la memoire que readline alloue
	}
}