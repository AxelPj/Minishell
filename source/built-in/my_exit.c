#include "../../include/header/minishell.h"

int	my_exit(char **args, t_exec *info, t_data *data, int bool)
{
	long	code;

	if (!args || !args[1])
	{
		if (bool == 1)
			free_partially(data, info);
		else
			free(info->fd);
		my_putstr_fd("exit\n", 1);
		free_and_exit(data, info, g_status);
	}
	if (!is_numeric(args[1]))
	{
		my_putstr_fd("exit\n", 1);
		my_putstr_fd("minishell: exit: ", 2);
		my_putstr_fd(args[1], 2);
		my_putstr_fd(": numeric argument required\n", 2);
		if (bool == 1)
			free_partially(data, info);
		else
			free(info->fd);
		free_and_exit(data, info, 2);
	}
	if (args[2])
		return (my_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	code = my_atol(args[1]);
	if (bool == 1)
		free_partially(data, info);
	else
		free(info->fd);
	my_putstr_fd("exit\n", 1);
	return (free_and_exit(data, info, (unsigned char)code), 0);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!my_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}


void	free_partially(t_data *data, t_exec *info)
{
	free_all(data);
	free_info(info);
}

void	free_and_exit(t_data *data, t_exec *info, int bool)
{
	data->envp_cpy = free_tab(data->envp_cpy);
	free(data);
	free(info);
	exit((unsigned char)bool);
}
