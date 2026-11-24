#include "minishell.h"

int	token_type(char *s_token)
{
	if (s_token[0] == '|')
		return (1);
	else if (s_token[0] == '<' && s_token[1] == '<')
		return (2);
	else if (s_token[0] == '>' && s_token[1] == '>')
		return (3);
	else if (s_token[0] == '>')
		return (4);
	else if (s_token[0] == '<')
		return (5);
	else if (s_token[0] == '>')
		return (2);
	else if (s_token[0] == '<')
		return (3);
	return (0);
}

t_pars	*sort_token(t_data *data, int i, int size)
{
	int		count;
	t_pars	*node;

	while (data->tab_token[i] && i < size)
	{
		count = count_token_word(i, data->tab_token, size);
		node = my_lst_parsnw(data->tab_token,
				token_type(data->tab_token[i]), &i, count);
		if (!data->parsing)
			data->parsing = node;
		else
			my_pars_lstadd_bck(&data->parsing, node);
		if (data->tab_token[i])
			i++;
	}
	return (data->parsing);
}

int	count_token_word(int i, char **tab_token, int size)
{
	int	count;

	count = 0;
	while (tab_token[i] && i < size)
	{
		if (tab_token[i] && token_type(tab_token[i]) != 0)
		{
			if (count > 0)
				return (count);
			else
				return (1);
		}
		else
			count++;
		i++;
	}
	return (count);
}
