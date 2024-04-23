/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:13:07 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/21 15:22:44 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	ft_repeatp(char *str)
{
	int		x;
	char	fq;

	fq = ' ';
	x = 0;
	while (str && str[x] && (str[x] != '|' || fq != ' '))
	{
		if (str[x] == '\'' || str[x] == '\"')
		{
			if (fq == str[x])
				return (1);
			else if (fq == '\'' || fq == '\"')
				return (0);
			else
				fq = str[x];
		}
		x++;
	}
	return (0);
}

static char	*ft_strcut(char *s, int a, int b)
{
	char	*res;
	int		x;
	int		y;

	res = s;
	y = 0;
	if (a > b)
		x = b;
	else
		x = a;
	while (s[y] && y != x)
	{
		res[y] = s[y];
		y++;
	}
	if (a > b)
		x = a + 1;
	else
		x = b + 1;
	while (s[x])
		res[y++] = s[x++];
	res[y] = '\0';
	return (res);
}

static int	ft_endorpipestr(char	*str, int	*ref, char *fq)
{
	int		x;
	char	q;

	*ref = -2;
	*fq = ' ';
	x = 0;
	q = ' ';
	while (str[x] && (str[x] != '|' || q != ' '))
	{
		if (q == ' ' && (str[x] == '\'' || str[x] == '\"'))
			q = str[x];
		else if (str[x] == q)
			q = ' ';
		x++;
	}
	return (x);
}

static char	*ft_nofinquot(char *str)
{
	int		x;
	int		ref;
	char	fq;

	x = ft_endorpipestr(str, &ref, &fq);
	while (x != 0)
	{
		if (str[x] == '\'' || str[x] == '\"')
		{
			if (fq == str[x] && x == ref - 1)
			{
				str = ft_strcut(str, x, ref);
				fq = ' ';
			}
			else if (fq != '\'' && fq != '\"')
			{
				fq = str[x];
				ref = x;
			}
			else if (str[x] == fq)
				fq = ' ';
		}
		x--;
	}
	return (str);
}

void	del_quotes(t_process *process)
{
	t_var	var;

	var.i = 0;
	var.token = process->argv;
	var.aux = ft_strdup("");
	while (var.token[var.i])
	{
		free (var.aux);
		var.tmp_join = ft_strdup("");
		var.j = 0;
		var.tmp = ft_splitcare(ft_nofinquot(var.token[var.i]));
		while (var.tmp[var.j])
			ft_add_var(&var);
		free(var.tmp);
		var.aux = var.token[var.i];
		var.tmp_join = ft_mod_parsequote(var);
		var.token[var.i] = var.tmp_join;
		if (check_split_quote(var.token[var.i]) && ft_repeatp(var.aux))
			var.i -= check_split_quote(var.token[var.i]);
		var.i++;
	}
	ft_protect_void_v(var.token);
	free (var.aux);
}
