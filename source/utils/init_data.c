/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:31:16 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/03 14:12:25 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

void	init_data(s_data *data, int bool, char **envp)
{
	data = malloc (sizeof (s_data));
	if (bool == 0)
		data->envp_cpy = envp_cpy(data, envp);
	else	
		(void) envp;
	
}
