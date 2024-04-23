/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:15:16 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:07 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	is_redirect(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

char	*ft_noquotes(char *str)
{
	int		x;
	int		y;

	x = 0;
	while (str[x] && str[x] != '\"' && str[x] != '\'')
		x++;
	if (str[x] && (str[x] == '\"' || str[x] == '\''))
		y = x;
	else
		return (str);
	x++;
	while (str[x] && str[x] != str[y])
		x++;
	if (!str[x])
		return (str);
	if (!str[x + 1])
		return (ft_noquotingredir(str, x, y));
	return (ft_complexnquotred(str, x, y));
}

char	*set_file_redirect(t_redirect *redirect, char *line)
{
	char	**file;
	int		i;
	char	qu;

	file = (char **)ft_sec_malloc(sizeof(char *) * 2);
	i = 0;
	qu = ' ';
	line = ft_isspace(line);
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && qu == ' ')
			qu = line[i];
		while (qu != ' ' && line[i])
		{
			i++;
			if ((line[i] == '\'' || line[i] == '\"') && line[i] == qu)
				qu = ' ';
		}
		if ((ft_isascii(line[i])) && line[i] != ' ' && !is_redirect(line[i]))
			i++;
		else
			break ;
	}
	ft_aux_set_file_red(file, redirect, i, line);
	return (&line[i]);
}

char	*set_symbol_redirect(t_redirect *redirect, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_redirect(line[i]))
			i++;
		else
			break ;
	}
	redirect->symbol = ft_strndup(line, i);
	return (&line[i]);
}

char	*get_redirect(char *line, t_process *lst_process)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)ft_sec_malloc(sizeof(t_redirect));
	line = ft_isspace(line);
	line = set_symbol_redirect(new_redirect, line);
	line = set_file_redirect(new_redirect, line);
	new_redirect->next = NULL;
	new_redirect->pos = 1;
	if (new_redirect->symbol[0] == '<')
	{
		if (!lst_process->input)
			lst_process->input = new_redirect;
		else
			ft_addlst_back_redirect(lst_process->input, new_redirect);
	}
	else
	{
		if (!lst_process->output)
			lst_process->output = new_redirect;
		else
			ft_addlst_back_redirect(lst_process->output, new_redirect);
	}
	return (line);
}
