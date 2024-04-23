/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parseo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:13:30 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/21 16:07:10 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static char	*init_parse(t_parseo *parse, char *line)
{
	char	*res;

	(*parse).i = 0;
	(*parse).num_arg = 1;
	(*parse).quotes_s = false;
	(*parse).quotes_d = false;
	res = ft_isspace(line);
	return (res);
}

static void	ft_quotes_afterpipe(char	*line, t_parseo	parse)
{
	if (line)
	{
		if (line[0] == '\'' && parse.quotes_d == false
			&& parse.quotes_s == false)
			parse.quotes_s = true;
		else if (line[0] == '\"' && parse.quotes_d == false
			&& parse.quotes_s == false)
			parse.quotes_d = true;
	}
}

int	get_num_pipe(char *line)
{
	t_parseo	parse;

	line = init_parse(&parse, line);
	if (*line != '|')
	{
		while (line[parse.i])
		{
			change_status_quote(line, &parse);
			if (line[parse.i] == '|' && parse.quotes_d == false
				&& parse.quotes_s == false)
			{
				*&(line[parse.i]) = '\0';
				line = ft_isspace(&line[parse.i + 1]);
				parse.i = 0;
				if (line[(parse.i)] == '|' || line[(parse.i)] == '\0')
					return (-1);
				(parse.num_arg)++;
				ft_quotes_afterpipe(line, parse);
			}
			else
				(parse.i)++;
		}
		return (parse.num_arg);
	}
	return (-1);
}

static int	ft_prepipe(char	*line)
{
	int	x;

	x = 0;
	while (line[x] && line[x] == ' ')
		x++;
	if (line[x] == '|')
		return (1);
	else
		return (0);
}

int	pre_parse(char *line)
{
	char	qu;

	qu = ' ';
	if (ft_prepipe(line))
		return (0);
	while (*line)
	{
		line = ft_isspace(line);
		line = ft_carequotes(line);
		line = ft_aux_pre_parse(line);
		if (line == NULL)
			return (0);
		if (*line == '|')
		{
			line++;
			line = ft_isspace(line);
			if (*line == '|' || *line == false)
				return (0);
		}
		if (*line && !is_redirect(*line))
			line++;
	}
	return (1);
}
