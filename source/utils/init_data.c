/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:31:16 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/17 15:15:56 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

s_data	*init_data(s_data *data, int bool, char **envp)
{
	data = malloc (sizeof(s_data));
	data->processed = NULL;
	data->tab_token = NULL;
	data->token_lst = NULL;
	data->index_input = 0;
	data->nb_token = 0;
	data->nb_pipe = 0;
	if (bool == 0)
		data->envp_cpy = envp_cpy(data, envp);
	else
		(void) envp;
	return (data);
}
