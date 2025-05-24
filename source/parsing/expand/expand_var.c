/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axel <axel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:49 by axel              #+#    #+#             */
/*   Updated: 2025/05/24 21:03:26 by axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_expand(t_data *data, t_pars *parsing)
{
    t_pars *current = parsing;

    while (current)
    {
        for (int i = 0; current->tab_tok[i]; i++)
        {
            int count_dol = count_dollars(current->tab_tok[i]);
            if (count_dol > 0)
            {
                char **tab = split_into_expand(current->tab_tok[i], data);
                if (tab)
                {
                    tab = change_var_to_value(tab, count_dol);
                    free(current->tab_tok[i]);
                    current->tab_tok[i] = join_expanded_tokens(tab);
                    free_tab(tab);
                }
            }
        }
        current = current->next;
    }
}

char **change_var_to_value(char **tab, int count_doll)
{
    for (int i = 0; tab[i] && count_doll > 0; i++)
    {
        if (tab[i][0] == '$')
        {
            char *var_name = extract_var_name(tab[i]);
            char *var_value = getenv(var_name);

            free(tab[i]);
            if (var_value)
                tab[i] = ft_strdup(var_value);
            else
                tab[i] = ft_strdup("");
            free(var_name);
            count_doll--;
        }
    }
    return (tab);
}

char *extract_var_name(char *s)
{
    char *var_name;
    int start = 0;
    int end = 0;

    start++;
    if (s[start] == '{')
    {
        start++;
        end = start;
        while (s[end] && s[end] != '}')
            end++;
        var_name = ft_substr(s, start, end - start);
    }
    else
    {
        end = start;
        while (s[end] && (ft_isalnum(s[end]) || s[end] == '_'))
            end++;
        var_name = ft_substr(s, start, end - start);
    }

    return (var_name);
}

char *join_expanded_tokens(char **tab)
{
    char *result = ft_strdup("");

    for (int i = 0; tab[i]; i++)
    {
        char *temp = result;
        result = ft_strjoin(result, tab[i]);
        free(temp);
    }

    return (result);
}
