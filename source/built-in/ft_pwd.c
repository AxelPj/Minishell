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
}
