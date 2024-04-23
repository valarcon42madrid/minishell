/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:00:04 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 17:40:38 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static int	ft_second_should(int x, char *line, int *did, char aux)
{
	int		p;
	char	aux2;

	aux2 = ' ';
	p = x;
	x = ft_compress_scsh_x(line, x);
	while (line[x] && line[x] != '|')
	{
		if (line[x] != '\'' && line[x] != '\"' && line[x] != ' ')
			aux = line[x];
		if (aux2 == '\"' && aux == '$')
			return (0);
		else if (aux2 == ' ' && line[x] == ' ' && *did == 0 && aux != ' ')
			return (++(*did));
		else if (aux2 != '\'' && aux2 != '\"')
			aux2 = line[x];
		else if (aux2 != line[x])
			return (0);
		else if (aux2 == line[x] && (ft_difquot(&(line[p])) || *did == 1))
			return (0);
		else if (aux2 == line[x])
			aux2 = ' ';
		x++;
	}
	return (ft_compress_sec_sh(aux, did, line, x));
}

static int	ft_shouldapply(char *line, int y, int *did)
{
	int	x;
	int	pipe;

	pipe = 0;
	x = 0;
	if (ft_esception(line) || *did == 1)
		return (0);
	while (x < y)
	{
		if (line[x] == '|')
			pipe++;
		x++;
	}
	x = 0;
	while (pipe != 0)
	{
		if (line[x] == '|')
			pipe--;
		x++;
	}
	return (ft_second_should(x, line, did, line[y - 1]));
}

static	char	*ft_newlenstr(char *line, int	*a, int *b, int *c)
{
	int	len;
	int	x;

	*a = 1;
	*b = -1;
	*c = 0;
	len = ft_strlen(line) + 1;
	x = 1;
	while (line[x - 1] && line[x])
	{
		if ((line[x - 1] == '\"' && line [x] == '\"')
			|| (line[x - 1] == '\'' && line [x] == '\''))
			len++;
		x++;
	}
	return ((char *)ft_sec_malloc(sizeof(char) * len));
}

static	char	*ft_forceerrorvoid(char *line, char *nwln, int x, int *len)
{
	nwln[x + *len] = line[x - 1];
	(*len)++;
	nwln[x + *len] = ' ';
	return (nwln);
}

char	*ft_justquotes(char	*line)
{
	int		x;
	int		len;
	char	*nwln;
	int		did;

	if (!line || !line[0])
		return (line);
	nwln = ft_newlenstr(line, &x, &len, &did);
	while (line[x - 1] && line[x])
	{
		if (((line[x - 1] == '\"' && line[x] == '\"') || (line[x - 1] == '\''
					&& line [x] == '\'')) && ft_shouldapply(line, x, &did))
			nwln = ft_forceerrorvoid(line, nwln, x, &len);
		else
			nwln[x + len] = line[x - 1];
		if (line[x] == '|')
			did = 0;
		x++;
	}
	if (line[x - 1])
		nwln[x + len] = line[x - 1];
	x++;
	nwln[x + len] = '\0';
	free (line);
	return (nwln);
}
