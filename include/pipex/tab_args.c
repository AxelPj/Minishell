/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:37:23 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/24 16:57:29 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tab_all_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:13:00 by lesalmon          #+#    #+#             */
/*   Updated: 2025/05/24 18:18:00 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static char	*ft_strdup_mini(const char *s)
{
	char	*dup;
	int		len;

	len = 0;
	while (s[len])
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dup[len] = s[len];
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

static int	count_cmds(char **tab)
{
	int	i;
	int	nb_cmds;

	i = 0;
	nb_cmds = 1;
	while (tab[i])
	{
		if (!strcmp(tab[i], "|"))
			nb_cmds++;
		i++;
	}
	return (nb_cmds);
}

static char	**extract_args(char **tab, int start, int end)
{
	int		len;
	int		i;
	char	**args;

	i = 0;
	len = end - start;
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	while (i < len)
	{
		args[i] = ft_strdup_mini(tab[start + i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	***tab_args(char **tab)
{
	int		i;
	int		j;
	int		start;
	int		nb_cmds;
	char	***all_args;

	i = 0;
	j = 0;
	start = 0;
	nb_cmds = count_cmds(tab);
	all_args = malloc(sizeof(char **) * (nb_cmds + 1));
	if (!all_args)
		return (NULL);
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], "|"))
		{
			all_args[j++] = extract_args(tab, start, i);
			start = i + 1;
		}
		i++;
	}
	all_args[j++] = extract_args(tab, start, i);
	all_args[j] = NULL;
	return (all_args);
}

void	free_tab_args(char ***cmds_args)
{
	int	i;
	int	j;

	i = 0;
	while (cmds_args && cmds_args[i])
	{
		j = 0;
		while (cmds_args[i][j])
		{
			free(cmds_args[i][j]);
			j++;
		}
		free(cmds_args[i]);
		i++;
	}
	free(cmds_args);
}
