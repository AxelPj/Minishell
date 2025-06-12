/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_modif_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:42:41 by axel              #+#    #+#             */
/*   Updated: 2025/05/29 12:46:04 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	skip_dq(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while (processed[start] && (!in_dq(processed[start])))
		start++;
	*i = start;
}

void	skip_sq(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while (processed[start] && (!in_sq(processed[start])))
		start++;
	*i = start;
}

void	skip_to_space_or_q(char *processed, int *i)
{
	int	start;

	start = *i;
	start++;
	while (processed[start] && !in_space(processed[start])
		&& !in_sq(processed[start]) && !in_dq(processed[start]))
		start++;
	*i = start;
}
