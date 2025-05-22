/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:source/built-in/ft_pwd.c
/*   Created: 2025/05/13 17:58:17 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/20 11:04:00 by lesalmon         ###   ########.fr       */
=======
/*   Created: 2025/05/02 17:31:16 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/17 15:15:56 by axelpeti         ###   ########.fr       */
>>>>>>> origin/main:source/utils/init_data.c
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

<<<<<<< HEAD:source/built-in/ft_pwd.c
int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
=======
s_data	*init_data(s_data *data, int bool, char **envp)
{
	data = malloc (sizeof(s_data));
	data->processed = NULL;
	data->tab_token = NULL;
	data->token_lst = NULL;
	data->index_input = 0;
	data->nb_token = 0;
	data->nb_pipe = 0;
	if (bool == 0)
		data->envp_cpy = envp_cpy(data, envp);
	else
		(void) envp;
	return (data);
>>>>>>> origin/main:source/utils/init_data.c
}
