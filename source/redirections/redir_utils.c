#include "minishell.h"

void	heredoc(t_exec *info, char **args, int cmd, int i)
{
	info->append[cmd] = my_strdup(args[++i]);
	info->infile[cmd] = setup_here_doc(info->append[cmd]);
	if (info->infile[cmd] < 0)
		return ;
}

void	append(t_exec *info, char **args, int cmd, int i)
{
	info->outfile[cmd] = my_strdup(args[++i]);
	info->out_flags[cmd] = O_CREAT | O_WRONLY | O_APPEND;
}

void	infile(t_exec *info, char **args, int cmd, int i)
{
	if (info->infile[cmd] == -2)
		return ;
	if (info->infile[cmd] >= 0)
		close(info->infile[cmd]);
	info->infile[cmd] = open(args[++i], O_RDONLY);
	if (info->infile[cmd] < 0)
	{
		my_putstr_fd("minishell: ", 2);
		perror(args[i]);
		info->infile[cmd] = -2;
	}
}

void	outfile(t_exec *info, char **args, int cmd, int i)
{
	info->outfile[cmd] = my_strdup(args[++i]);
	info->out_flags[cmd] = O_CREAT | O_WRONLY | O_TRUNC;
}
