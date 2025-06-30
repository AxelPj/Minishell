/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:37:34 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/30 18:26:10 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe_edges(char *s, int i)
{
	if (!ft_strchr(s, '|'))
		return (0);
	if (check_pipe_syntax_error2(s, 0))
		return (2);
	while (s[i] && in_space(s[i]))
		i++;
	if (s[i] == '|')
	{
		i++;
		if (check_pipe_syntax_error(s, i, 0))
			return (1);
	}
	i = ft_strlen(s);
	i--;
	while (i >= 0 && in_space(s[i]))
		i--;
	if (i >= 0 && s[i] == '|')
	{
		i--;
		if (check_pipe_syntax_error(s, i, 1))
			return (1);
	}
	return (0);
}

int	check_pipe_syntax_error(char *s, int i, int bool)
{
	if (bool == 1)
	{
		while (i >= 0 && in_space(s[i]))
			i--;
		if (i >= 0 && s[i] == '|')
			return (ft_putstr_fd("near unexpected token '`||'\n", 1), 2);
		else
			return (ft_putstr_fd("near unexpected token '`|'\n", 1), 2);
	}
	else
	{
		while (in_space(s[i]))
			i--;
		if (i >= 0 && s[i] == '|')
			return (ft_putstr_fd("near unexpected token '`||'\n", 1), 2);
		else
			return (ft_putstr_fd("near unexpected token '`|'\n", 1), 2);
	}
	return (0);
}

int	check_pipe_syntax_error2(char *s, int j)
{
	while (s[j])
	{
		if (s[j] == '|')
		{
			j++;
			while (s[j])
			{
				if (s[j] != '|' && in_space(s[j]))
					break ;
				if (s[j] == '|')
				{
					ft_putstr_fd("near unexpected token '`||'\n", 2);
					return (1);
				}
				j++;
			}
		}
		j++;
	}
	return (0);
}

void	pass_quote(char *s, int *i, char c)
{
	int	start;

	start = *i;
	start++;
	while (s[start] != c)
		start++;
	*i = start + 1;
}