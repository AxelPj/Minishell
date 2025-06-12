/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lesalmon <lesalmon@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:31:16 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/24 14:38:56 by lesalmon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/header/minishell.h"

t_data	*init_data(t_data *data, int bool, char **envp)
{
	data = malloc (sizeof(t_data));
	data->parsing = NULL;
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
	set_shell(data);
	return (data);
}
