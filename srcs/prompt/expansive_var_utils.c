/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansive_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:12:30 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 13:38:26 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	len_expansive(t_var *var)
{
	var->j++;
	var->len_exp = 0;
	while (var->token[var->i][var->j]
		&& (var->token[var->i][var->j] != ' '
		&& var->token[var->i][var->j] != '$'
		&& var->token[var->i][var->j] != '/'
		&& var->token[var->i][var->j] != '='
		&& var->token[var->i][var->j] != '\0'
		&& !is_quote(var->token[var->i][var->j])))
	{
		var->len_exp++;
		var->j++;
	}
}

int	get_num_words_matrix(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	**matrixjoin(char **str1, char **str2, int insec_point)
{
	char	**new_matrix;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = get_num_words_matrix(str1) + get_num_words_matrix(str2);
	new_matrix = (char **)ft_sec_malloc(sizeof(char *) * (len));
	if (!str2 || !str2[0])
		new_matrix[0] = ft_strdup("");
	while (i < insec_point)
	{
		new_matrix[i] = ft_strdup(str1[i]);
		i++;
	}
	while (str2 && str2[j])
	{
		new_matrix[i + j] = ft_strdup(str2[j]);
		j++;
	}
	while (str1[++i])
		new_matrix[i + j - 1] = ft_strdup(str1[i]);
	new_matrix[len - 1] = NULL;
	return (new_matrix);
}

void	loop_expa_redirect_input(t_shell *shell, t_redirect *redirect)
{
	while (redirect)
	{
		if (ft_strcmp(redirect->symbol, "<<\0"))
		{
			expansive_token_input(shell, redirect->file);
			del_quotes_redirect(redirect);
		}
		redirect = redirect->next;
	}
}

void	loop_expa_redirect_output(t_shell *shell, t_redirect *redirect)
{
	while (redirect)
	{
		expansive_token_output(shell, redirect->file);
		del_quotes_redirect(redirect);
		redirect = redirect->next;
	}
}
