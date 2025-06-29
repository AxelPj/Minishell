/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 19:27:55 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/29 21:48:47 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	char	*ret;
	char	c;
	int		i;
	int		cpt;

	cpt = 0;
	i = 0;
	ret = malloc(9999);
	if (fd < 0)
		return (NULL);
	cpt = read(fd, &c, 1);
	while ((cpt > 0))
	{
		ret[i] = c;
		i++;
		if (c == '\n')
			break ;
		cpt = read(fd, &c, 1);
	}
	if (i == 0 || cpt < 0)
		return (free(ret), NULL);
	ret[i] = '\0';
	return (ret);
}
