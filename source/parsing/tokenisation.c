/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:31:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/05/03 15:49:08 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_delimiter(char c)
{
	char	*del;
	int		i;

	i = 0;
	del = "\t\n\"'()<>|$&;{}[]`";
	while (del[i])
	{
		if (del[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*space_to_input(char *input, int len, int i, int j)
{
	char	*processed;

	processed = malloc (2 * len + 1);
	while (input[i])
	{
		if (is_delimiter(input[i]) == 1)
		{
			processed[j] = " ";
			processed[j] = input[i];
			processed[j] = " ";
			i++;
			j++;
		}
		else 
		{
			processed[j] = input[i];
			j++;
			i++;
		}
	}
	processed[j] = '\0';
	return (processed);
}
