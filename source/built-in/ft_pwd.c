/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:58:17 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/22 13:39:20 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

int	ft_pwd(t_data *data)
{
	char	*cwd;
	int		i;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		while (data->envp_cpy[i])
		{
			if (!ft_strncmp(data->envp_cpy[i], "PWD=", 4))
			{
				printf("%s\n", data->envp_cpy[i]);
				return (0);
			}
			i++;
		}
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
