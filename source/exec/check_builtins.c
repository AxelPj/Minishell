#include "minishell.h"

int	is_builtin_child(char *cmd)
{
	if (!cmd)
		return (0);
	if (!my_strcmp(cmd, "echo") || !my_strcmp(cmd, "env") \
		|| !my_strcmp(cmd, "pwd"))
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!my_strcmp(cmd, "echo")
		|| !my_strcmp(cmd, "cd")
		|| !my_strcmp(cmd, "pwd")
		|| !my_strcmp(cmd, "export")
		|| !my_strcmp(cmd, "unset")
		|| !my_strcmp(cmd, "env")
		|| !my_strcmp(cmd, "exit"));
}

int	is_valid_builtin(char *cmd)
{
	if (!my_strncmp(cmd, "echo", 4))
		return (0);
	else if (!my_strncmp(cmd, "cd", 2))
		return (0);
	else if (!my_strncmp(cmd, "pwd", 3))
		return (0);
	else if (!my_strncmp(cmd, "export", 6))
		return (0);
	else if (!my_strncmp(cmd, "unset", 5))
		return (0);
	else if (!my_strncmp(cmd, "env", 3))
		return (0);
	else if (!my_strncmp(cmd, "exit", 4))
		return (0);
	return (1);
}

int	is_builtin_parent(char *cmd)
{
	if (!cmd)
		return (0);
	if (!my_strncmp(cmd, "cd", 2))
		return (1);
	if (!my_strncmp(cmd, "export", 6))
		return (1);
	if (!my_strncmp(cmd, "unset", 5))
		return (1);
	if (!my_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

int	execute_builtin(char *cmd, char **args, t_exec *info, t_data *data)
{
	if (!cmd)
		return (1);
	if (!my_strncmp(cmd, "cd", 2))
	{
		if (args[1] && args[2])
		{
			my_putstr_fd("cd: too many arguments\n", 2);
			return (1);
		}
		return (my_cd(args, data));
	}
	if (!my_strncmp(cmd, "echo", 4))
		return (my_echo(args, STDOUT_FILENO));
	if (!my_strncmp(cmd, "pwd", 3))
		return (my_pwd(data, args[1]));
	if (!my_strncmp(cmd, "env", 3))
		return (my_env(data));
	if (!my_strncmp(cmd, "export", 6))
		return (my_export(info, data));
	if (!my_strncmp(cmd, "unset", 5))
		return (my_unset(data, args));
	if (!my_strncmp(cmd, "exit", 4))
		return (my_exit(args, info, data, 1));
	return (1);
}
