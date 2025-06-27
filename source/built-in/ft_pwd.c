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

void	pwd_copy(t_data *data, int i, int j, int k, char *cwd)
{
	while (data->envp_cpy[i])
	{
		if (!ft_strncmp(data->envp_cpy[i], "PWD=", 4))
		{
			cwd = malloc(sizeof(char *) * (ft_strlen(data->envp_cpy[i]) - 3));
			while (data->envp_cpy[i][k])
			{
				cwd[j] = data->envp_cpy[i][k];
				j++;
				k++;
			}
			printf("%s\n", cwd);
		}
		i++;
	}
}

int	ft_pwd(t_data *data, char *arg)
{
	char	*cwd;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 5;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL && (ft_strcmp(arg, "..") == 0))
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access"
			"parent directories: No such file or directory\n", 2);
		return (0);
	}
	else if (!cwd)
	{
		pwd_copy(data, i, j, k, cwd);
		return (0);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
