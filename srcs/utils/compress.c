/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:27:23 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 17:14:54 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	ft_compress_sec_sh(char aux, int *did, char *line, int x)
{
	if ((aux == '!' || ((int)aux > 34 && (int)aux < 127
				&& (int)aux != 39) || ((int)aux < 0)) && (int)aux != 36)
		return (0);
	if ((!line[x] || line[x] == '|') && *did == 0 && (int)aux > 0)
		return (++(*did));
	return (0);
}

void	ft_compress_ex_tk_aux(t_var	*var)
{
	var->j++;
	while (var->token[var->i][var->j]
			&& var->token[var->i][var->j] != '\'')
		var->j++;
}

void	ft_compress_extk_swp(t_var	*var, t_shell	*shell, int np)
{
	if (var->token[var->i][var->j] == '$'
			&& (!var->token[var->i][var->j + 1]
			|| (var->token[var->i][var->j + 1] != ' ')))
	{
		if (!var->token[var->i][var->j + 1]
			|| (((var->token[var->i][var->j + 1] == '\''
			|| var->token[var->i][var->j + 1] == '\"')
			&& (var->bool == true || !var->token[var->i][var->j + 2]))))
			var->j++;
		else
		{
			len_expansive(var);
			expansive_swap(shell, var, np);
		}
	}
}

int	ft_compress_swp_aux(char **tmp_matrix, t_var	*var)
{
	int	aux;

	aux = 0;
	while (tmp_matrix[var->i + aux])
		aux++;
	aux--;
	return (aux);
}

int	ft_compress_scsh_x(char *line, int x)
{
	while (line[x] && line[x] == ' ')
		x++;
	return (x);
}
