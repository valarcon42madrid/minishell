/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:13:16 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/21 15:58:28 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

char	*next_token(char *line)
{
	line = ft_isspace(line);
	while (is_redirect(*line))
	{
		while (is_redirect(*line))
			line++;
		line = ft_isspace(line);
		while (*line && *line != ' ' && !is_redirect(*line))
			line++;
		line = ft_isspace(line);
	}
	return (line);
}

int	len_token(char *line)
{
	t_parseo	parse;

	parse.i = 0;
	parse.quotes_d = false;
	parse.quotes_s = false;
	change_status_quote(line, &parse);
	while ((line[parse.i] && line[parse.i] != ' ')
		|| parse.quotes_d == true || parse.quotes_s == true)
	{
		(parse.i)++;
		change_status_quote(line, &parse);
	}
	return (parse.i);
}

char	**get_tokens_arg(t_process *process, char *line)
{
	char	**arguments;
	int		pos_arg;
	int		size;
	int		len;

	len = 0;
	pos_arg = 0;
	size = num_arg_process(line, process);
	if (size == 0)
		return (NULL);
	arguments = (char **)ft_sec_malloc(sizeof(char *) * (size + 1));
	while (pos_arg < size)
	{
		line = next_token(line);
		len = len_token(line);
		arguments[pos_arg] = ft_strndup(line, len);
		line = &line[len];
		pos_arg++;
		len = 0;
	}
	arguments[size] = NULL;
	return (arguments);
}
