/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:53:13 by axelpeti          #+#    #+#             */
/*   Updated: 2024/11/07 18:54:24 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int nmemb, int size)
{
	void	*tab;
	size_t	total_size;

	total_size = (size_t)nmemb * size;
	if (total_size == 0)
		return (NULL);
	tab = malloc(total_size);
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, total_size);
	return (tab);
}
