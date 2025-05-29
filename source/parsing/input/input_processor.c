/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:32:20 by axel              #+#    #+#             */
/*   Updated: 2025/05/29 16:45:06 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_join(t_data *data, char *s2, int start, int end)
{
	size_t	i;
	char	*new_processed;
	size_t	k;

	k = 0;
	if (!data->processed)
		new_processed = malloc((end - start) + 3);
	else
		new_processed = malloc(ft_strlen(data->processed) + (end - start) + 3);
	i = 0;
	while (data->processed && data->processed[i])
		new_processed[k++] = data->processed[i++];
	if ((start > 0 && in_space(s2[start - 1]) == 1)
		|| (start > 0 && is_one_delimiter(s2[start - 1]) == 1)
		|| is_one_delimiter(s2[start]) == 1)
		new_processed[k++] = ' ';
	while (start < end)
		new_processed[k++] = s2[start++];
	new_processed[k++] = '\0';
	if (data->processed)
		free(data->processed);
	data->index_input = end;
	return (new_processed);
}

char	*process_join_quote(t_data *data, char *s2, int start, int end)
{
	size_t	i;
	char	*new_processed;
	size_t	k;

	k = 0;
	if (!data->processed)
		new_processed = malloc ((end - start) + 3);
	else
		new_processed = malloc (ft_strlen(data->processed) + (end - start) + 3);
	i = 0;
	while (data->processed && data->processed[i])
		new_processed[k++] = data->processed[i++];
	if ((in_space(s2[start - 1]) == 1 && in_dq(s2[start]))
		|| (in_space(s2[start - 1]) == 1 && in_sq(s2[start])))
		new_processed[k++] = ' ';
	while (start < end)
		new_processed[k++] = s2[start++];
	new_processed[k++] = '\0';
	if (data->processed)
		free(data->processed);
	data->index_input = end;
	return (new_processed);
}
