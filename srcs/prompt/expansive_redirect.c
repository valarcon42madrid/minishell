/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansive_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:11:56 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/18 13:03:58 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	expansive_token_aux_2(t_shell *shell, t_var *var)
{
	var->j = 0;
	while (var->token[var->i][var->j])
	{
		if (var->token[var->i][var->j] == '\'')
		{
			var->j++;
			while (var->token[var->i][var->j]
					&& var->token[var->i][var->j] != '\'')
				var->j++;
		}
		if (var->token[var->i][var->j] == '$'
			&& var->token[var->i][var->j + 1]
			&& (var->token[var->i][var->j + 1] != ' '))
		{
			len_expansive(var);
			var->j -= var->len_exp;
			var->env = ft_strndup(&var->token[var->i][var->j], var->len_exp);
			expansive_swap_case2(shell, var);
			free(var->env);
		}
		if (ft_strlen(var->token[var->i]) <= (size_t)var->j)
			break ;
		var->j++;
	}
}

void	del_quotes_redirect(t_redirect *redirect)
{
	t_var	var;

	var.i = 0;
	var.token = redirect->file;
	while (var.token[var.i])
	{
		var.tmp_join = ft_strdup("");
		var.j = 0;
		var.tmp = ft_split(var.token[var.i],
				get_quotes_split(var.token[var.i]));
		while (var.tmp[var.j])
		{
			var.aux = var.tmp_join;
			var.tmp_join = ft_strjoin(var.tmp_join, var.tmp[var.j]);
			free(var.aux);
			free(var.tmp[var.j++]);
		}
		free(var.tmp);
		var.aux = var.token[var.i];
		var.token[var.i] = var.tmp_join;
		free(var.aux);
		var.i -= check_split_quote(var.token[var.i]);
		var.i++;
	}
}

char	*ft_noquotingredir(char *str, int x, int y)
{
	char	*aux;
	char	*res;

	if (y != 0)
	{
		aux = ft_strndup(str, y);
		res = ft_strndup(&str[y + 1], (x - y - 1));
		free (str);
		str = ft_strjoin(aux, res);
		free (aux);
		free (res);
		return (str);
	}
	else
	{
		res = ft_strndup(&str[y + 1], (x - y - 1));
		free (str);
		return (res);
	}
	return (str);
}

char	*ft_nqredaux(char	*str, int x, int y)
{
	char	*q;
	char	*res;
	char	*aux;

	q = ft_noquotes(ft_strdup(&str[x + 1]));
	aux = ft_strndup(str, y);
	res = ft_strndup(&str[y + 1], (x - y - 1));
	free (str);
	str = ft_strjoin(aux, res);
	free (aux);
	free (res);
	res = ft_strjoin(str, q);
	free (q);
	return (res);
}

char	*ft_complexnquotred(char *str, int x, int y)
{
	char	*res;
	char	*q;

	if (y != 0)
		return (ft_nqredaux(str, x, y));
	else
	{
		q = ft_noquotes(ft_strdup(&str[x + 1]));
		res = ft_strndup(&str[y + 1], (x - y - 1));
		free (str);
		str = ft_strjoin(res, q);
		free (res);
		free (q);
	}
	return (str);
}
