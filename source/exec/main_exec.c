#include "minishell.h"

void	launch_child(int idx, t_exec *info, t_data *data)
{
	setup_input(idx, info);
	setup_output(idx, info);
	close_pipes(info);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin_child(info->tab_args[idx][0]))
		builtin_exec(info, idx, data);
	command(info, data->envp_cpy, idx, data);
	exit(126 + g_status);
}

int	exec_main(t_data *data, t_exec *info)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (is_builtin(info->tab_args[0][0]) &&
		is_builtin_parent(info->tab_args[0][0]) &&
		info->nb_cmds < 2 && !info->outfile[0])
	{
		g_status = execute_builtin(info->tab_args[0][0],
				info->tab_args[0], info, data);
		return (0);
	}
	while (i < info->nb_cmds)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			launch_child(i, info, data);
		i++;
	}
	if (info->fd)
		close_all_pipes(info->fd, info->nb_cmds - 1);
	wait_all_children(info->nb_cmds);
	return (0);
}

int	exec_setup(t_data *data, char **tab, t_exec *info)
{
	int		i;
	char	**new_args;

	g_status = 0;
	i = 0;
	while (tab[i])
	{
		count_nb(info, tab, i);
		i++;
	}
	info = init_infos(info);
	info_heredoc(info);
	i = 0;
	while (info->tab_args[i])
	{
		new_args = rm_redir(info->tab_args[i]);
		free_split(info->tab_args[i]);
		info->tab_args[i] = new_args;
		i++;
	}
	setup_redir(info, tab);
	exec_main(data, info);
	free_info(info);
	return (0);
}
