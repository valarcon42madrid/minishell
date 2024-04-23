/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compressprompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 19:55:42 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 17:39:08 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

t_parseo	ft_init_arg_of_num_proc(void)
{
	t_parseo	parse;

	parse.quotes_d = false;
	parse.quotes_s = false;
	parse.num_arg = 0;
	parse.flag = false;
	parse.i = 0;
	return (parse);
}

char	*ft_aux_pre_parse(char *line)
{
	char	aux;

	if (is_redirect(*line))
	{
		while (is_redirect(*line))
			line++;
		line = ft_isspace(line);
		if (*line == '|' || *line == false || is_redirect(*line))
			return (NULL);
		else if (*line == '\'' || *line == '\"')
		{
			aux = *line;
			line++;
			while (*line && *line != aux)
				line++;
			if (!*line)
				return (NULL);
			else
			{
				line++;
				return (line);
			}
		}
	}
	return (line);
}

void	ft_aux_set_file_red(char **file, t_redirect *redirect,
			int i, char *line)
{
	file[0] = ft_noquotes(ft_strndup(line, i));
	file[1] = NULL;
	redirect->file = file;
}

void	ft_sytax_error(void)
{
	ft_putstr_fd("42_MiniShell: syntax error ", 2);
	ft_putendl_fd("near unexpected token", 2);
	g_error_code = 258;
}

char	*ft_carequotes(char *line)
{
	char	qu;

	qu = ' ';
	if ((*line == '\'' || *line == '\"' ) && qu == ' ')
	{
		qu = *line;
		line++;
		while (*line && *line != qu)
			line++;
		if (*line == qu)
		{
			qu = ' ';
			line++;
		}
	}
	return (line);
}
