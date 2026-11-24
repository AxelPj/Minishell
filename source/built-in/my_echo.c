#include "../../include/header/minishell.h"

int	is_all_n(char *s)
{
	int	i;

	i = 2;
	if (!s || s[0] != '-' || s[1] != 'n')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_n(char **input)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (input[i] && is_all_n(input[i]))
	{
		count++;
		i++;
	}
	return (count);
}

int	my_echo(char **input, int fd)
{
	int	i;
	int	n;
	int	nnb;

	i = 1;
	n = 1;
	nnb = check_n(input);
	if (nnb > 0)
	{
		n = 0;
		i += nnb;
	}
	while (input[i])
	{
		my_putstr_fd(input[i], fd);
		if (input[i + 1])
			my_putchar_fd(' ', fd);
		i++;
	}
	if (n)
		my_putchar_fd('\n', fd);
	return (0);
}
