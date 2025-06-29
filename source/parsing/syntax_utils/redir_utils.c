/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:43:44 by axelpeti          #+#    #+#             */
/*   Updated: 2025/06/29 17:21:28 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char c)
{
	return (c == '<' || c == '>');
}

int	redir_error_at(char *s, int i, char c, int count)
{
	if (!s[i] && count <= 2)
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	else if (count > 2)
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &c, 1);
		if (count > 3)
			write(2, &c, 1);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	else if (is_redir(s[i]))
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		write(2, &s[i], 1);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

int	check_redir_syntax_all(char *s, int i, int count, char c)
{
	while (s[i])
	{
		if (is_redir(s[i]))
		{
			c = s[i];
			count = 0;
			while (s[i] && (s[i] == c || in_space(s[i])))
				if (s[i++] == c)
					count++;
			while (s[i] && in_space(s[i]) && !is_redir(s[i]))
				i++;
			if (redir_error_at(s, i, c, count))
				return (1);
			while (is_redir(s[i]))
				i++;
		}
		else
			i++;
	}
	return (0);
}


