/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:47:32 by lesalmon          #+#    #+#             */
/*   Updated: 2025/06/12 18:13:28 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split_exec(char **result, size_t i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

static char	*ft_substr_pipex(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	c;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) <= start)
		return (ft_strdup(""));
	c = ft_strlen(s + start);
	if (c < len)
		len = c;
	s2 = malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	c = 0;
	while (c < len && s[start + c] != '\0')
	{
		s2[c] = s[start + c];
		c++;
	}
	s2[c] = '\0';
	return (s2);
}

static size_t	count_words_pipex(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (!s || s[i] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*get_word_pipex(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (ft_substr_pipex(s, 0, len));
}

char	**ft_split_exec(char const *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	word_count = count_words_pipex(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (i < word_count)
	{
		while (*s && *s == c)
			s++;
		result[i] = get_word_pipex(s, c);
		if (!result[i])
			free_split_exec(result, i);
		s += ft_strlen(result[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
