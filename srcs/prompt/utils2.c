/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:15:43 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/21 13:05:42 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	get_num_words(char **str)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!str[0])
		return (0);
	if (ft_strchr(str[0], '='))
		return (1);
	tmp = ft_split(str[0], ' ');
	while (tmp[i])
		i++;
	free_matrix(tmp);
	return (i);
}

int	get_num_words_join(char **argv)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (argv[i])
	{
		len += get_num_words(&argv[i]);
		i++;
	}
	return (len);
}

int	error_quote(t_parseo parse)
{
	if (parse.quotes_d == true || parse.quotes_s == true)
	{
		ft_putstr_fd("42_MiniShell: syntax error: unexpected open quote\n", 2);
		g_error_code = 258;
		return (0);
	}
	return (parse.num_arg);
}

char	get_quotes_split(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (is_quote(arg[i]))
			return (arg[i]);
		i++;
	}
	return ('\"');
}

int	check_split_quote(char *arg)
{
	int	quote_d;
	int	quote_s;
	int	i;

	quote_d = 0;
	quote_s = 0;
	i = 0;
	while (arg[i])
	{
		if (is_quote(arg[i]))
		{
			if (arg[i] == '\'')
				quote_s++;
			else
				quote_d++;
		}
		i++;
	}
	if (quote_s == 2 || quote_d == 2)
		return (1);
	return (0);
}
