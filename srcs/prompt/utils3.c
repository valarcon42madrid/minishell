/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:30:41 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/29 19:31:16 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static char	*ft_strspl(int q, int aux, char *str, int extra)
{
	char	*res;
	int		x;

	x = 0;
	res = (char *)ft_sec_malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[x + extra])
	{
		if (str[x + extra] != q && str[x + extra] != aux)
			res[x] = str[x + extra];
		else
			break ;
		x++;
	}
	res[x] = '\0';
	return (res);
}

static char	*ft_seg_quote(char *str, char q)
{
	int		extra;
	char	aux;

	if (str[0] == q && q != 'x')
		extra = 1;
	else
		extra = 0;
	if (q == 'x')
	{
		q = '\'';
		aux = '\"';
	}
	else
		aux = '\0';
	return (ft_strspl(q, aux, str, extra));
}

static char	**ft_justres(char	*str)
{
	char	**res;

	res = ft_sec_malloc(sizeof(char *) * 2);
	res[0] = ft_strdup(str);
	res[1] = NULL;
	return (res);
}

static char	**ft_res_split(int size, char *str)
{
	int		y;
	int		x;
	char	**res;

	res = ft_sec_malloc(sizeof(char *) * size);
	y = 0;
	x = 0;
	while (str[x])
	{
		if ((str[x] == '\'' || str[x] == '\"'))
		{
			res[y] = ft_seg_quote(&(str[x]), str[x]);
			x += ft_strlen(res[y]) + 2;
			y++;
		}
		else
		{
			res[y] = ft_seg_quote(&(str[x]), 'x');
			x += (ft_strlen(res[y]));
			y++;
		}
	}
	res[y] = NULL;
	return (res);
}

char	**ft_splitcare(char	*str)
{
	int		x;
	int		y;
	char	q;

	y = 2;
	x = 0;
	while (str[x] && str[x] != '\"' && str[x] != '\'')
		x++;
	if (str[x] == '\'' || str[x] == '\"')
		q = str[x];
	else
		return (ft_justres(str));
	x++;
	while (str[x])
	{
		if (str[x] == q)
		{
			y += 2;
			q = '\0';
		}
		else if (q == '\0' && (str[x] == '\'' || str[x] == '\"'))
			q = str[x];
		x++;
	}
	return (ft_res_split(y, str));
}
