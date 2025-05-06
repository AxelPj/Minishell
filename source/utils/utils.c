/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:29:04 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/06 17:03:50 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

char	**envp_cpy(s_data *data, char **envp)
{
	int	i;
	int	sizelen;

	sizelen = tablen((void **)envp);
	i = 0;
	data->envp_cpy = malloc (sizeof sizelen + 1);
	while (i < sizelen)
	{
		data->envp_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	data->envp_cpy[i] = NULL;
	return (data->envp_cpy);
}

int	verif_built_in(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return(1);
	else if (!ft_strcmp(str, "cd"))
		return(2);
	else if (!ft_strcmp(str, "pwd"))
		return(3);
	else if (!ft_strcmp(str, "export"))
		return(4);
	else if (!ft_strcmp(str, "unset"))
		return(5);
	else if (!ft_strcmp(str, "env"))
		return(6);
	else if (!ft_strcmp(str, "exit"))
		return(7);
	return (0);
} // fonction pour verifier si on est sur un built_in et savoir lequel est-ce
