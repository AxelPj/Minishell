/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:35:17 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/02 17:52:35 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header/minishell.h"

int main (int argc, char **argv, char **envp)
{
	char	*line;
	s_data	*data;

	data = NULL;
	if (envp)
		init_data(data, 0, envp);
	else
		init_data(data, 1, envp); // jai mis un int comme boolean pour savoir si on copi l'env en fonction de si on le donne a la compilation ou pas (1) pour non, (0) pour oui
	while(1)
		{
			line = readline("ZGEGDEOUF");
			printf("%s\n", line);
		}
}