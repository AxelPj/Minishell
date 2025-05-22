/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:29:04 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/22 13:37:14 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

char	**envp_cpy(t_data *data, char **envp)
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
}

char	*ft_tokenjoin(t_data *data, char *s1, char *s2, int start, int end)
{
	size_t	i;
	char *new_processed;
	size_t	k;

	k = 0;
	if (!s1)
		new_processed = malloc ((end - start) + 3);	
	else
		new_processed = malloc (ft_strlen(s1) + (end - start) + 3);
	i = 0;
	while (s1 && s1[i])
		new_processed[k++] = s1[i++];
	if (in_space(s2[start - 1]) || is_one_delimiter(s2[start])
		|| is_one_delimiter(s2[start - 1]))
		new_processed[k++] = ' ';
 	while (start < end)
		new_processed[k++] = s2[start++];
	new_processed[k++] = '\0';
	if (s1)
		free(s1);
	data->index_input = end;
	return (new_processed);
}

char	*ft_tokenquote(t_data *data, char *s1, char *s2, int start, int end)
{
	size_t	i;
	char *new_processed;
	size_t	k;
	
	k = 0;
	if (!s1)
		new_processed = malloc ((end - start) + 3);	
	else
		new_processed = malloc (ft_strlen(s1) + (end - start) + 3);
	i = 0;
	while (s1 && s1[i])
		new_processed[k++] = s1[i++];
	 if ((in_space(s2[start - 1]) == 1 && in_dq(s2[start]))
	 	|| (in_space(s2[start - 1]) == 1 && in_sq(s2[start])))
	new_processed[k++] = ' ';
 	while (start < end)
		new_processed[k++] = s2[start++];
	new_processed[k++] = '\0';
	if (s1)
		free(s1);
	data->index_input = end;
	return (new_processed);
}

int	is_two_delimiter(char c1, char c2)
{
	const char	*pairs[] = { ">>", "<<" };
	int			i;

	i = 0;
	while (i < 2)
	{
		if (c1 == pairs[i][0] && c2 == pairs[i][1])
			return (1);
		i++;
	}
	return (0);
}

int	is_one_delimiter(char c)
{
	char	*del;
	int		i;

	i = 0;
	del = "()<>|${}[]`";
	while (del[i])
	{
		if (del[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	print_lst(t_data *data)
{
	t_list *current;

	current = data->token_lst;
	while (current->next)
	{
		printf("str token = %s token = %d a l'index %d\n", current->s, current->token, current->index);
		current = current->next;
	}
	printf("str token = %s token = %d a l'index %d\n", current->s, current->token, current->index);
}

void	print_pars_lst(t_data *data)
{
	t_pars *current;
	int i;
	printf ("token parse =\n\n");
	current = data->parsing;
	while (current->next)
	{
		i = 0;
		while (current->tab_tok[i])
		{
			printf("tab_tok = %s\n", current->tab_tok[i]);
			i++;
		}
		printf("token = %d a l'index %d\n", current->token, current->index);
		current = current->next;
	}
	i = 0;
	while (current->tab_tok[i])
		{
			printf("tab_tok = %s\n", current->tab_tok[i]);
			i++;
		}
}