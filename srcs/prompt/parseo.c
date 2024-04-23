/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:12:55 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/21 15:58:52 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	state_var(char *line, t_parseo *parse)
{
	if (*line && *line != ' ' && !is_redirect(*line)
		&& parse->flag == false
		&& parse->quotes_d == false && parse->quotes_s == false)
	{
		(parse->num_arg)++;
		parse->flag = true;
	}
}

int	num_arg_process(char *line, t_process *lst_process)
{
	t_parseo	parse;
	char		c;

	parse = ft_init_arg_of_num_proc();
	while (*line)
	{
		c = *line;
		if (is_redirect(c) && parse.quotes_d == false
			&& parse.quotes_s == false)
			line = get_redirect(line, lst_process);
		c = *line;
		if ((c == ' ' || is_redirect(c)) && (parse.quotes_d == false
				&& parse.quotes_s == false))
			parse.flag = false;
		change_status_quote(line, &parse);
		state_var(line, &parse);
		if (!*line)
			break ;
		if (!is_redirect(*line) || parse.quotes_s == true
			|| parse.quotes_d == true)
			line++;
	}
	return (error_quote(parse));
}

static char	*next_line_process(char *line)
{
	char	q;

	q = ' ';
	while (*line && (*line != '|' || q != ' '))
	{
		if (q == ' ' && (*line == '\'' || *line == '\"'))
			q = *line;
		else if (*line == q)
			q = ' ';
		line++;
	}
	line++;
	return (line);
}

static char	*ft_strdupprotected(char *line)
{
	int		x;
	int		y;
	char	*res;

	y = 0;
	x = 0;
	while (line[x] && (line[x] == ' ' || line[x] == -62))
		x++;
	while (line[x] && line[x + 1] && y == 0)
	{
		if (line[x] == '\'' && line[x + 1] == '\'' && y == 0)
			x += 2;
		else if (line[x] == '\"' && line[x + 1] == '\"' && y == 0)
			x += 2;
		else
			y = 1;
	}
	res = ft_strdup(&(line[x]));
	return (res);
}

char	**get_lines_cmd(char *line, int num_process)
{
	char	**lines_cmd;
	int		i;

	i = 1;
	lines_cmd = (char **)ft_sec_malloc(sizeof(char *) * (num_process + 1));
	if (!lines_cmd)
		return (NULL);
	lines_cmd[0] = ft_strdupprotected(line);
	if (!lines_cmd[0])
		return (NULL);
	if (num_process > 1)
	{
		while (i < num_process)
		{
			line = next_line_process(line);
			lines_cmd[i] = ft_strdup(line);
			if (!lines_cmd[i])
				return (NULL);
			i++;
		}
	}
	lines_cmd[num_process] = NULL;
	return (lines_cmd);
}
