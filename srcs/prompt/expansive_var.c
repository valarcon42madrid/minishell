/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansive_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:12:20 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 11:00:23 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	expansive_token_aux(t_shell *shell, t_var *var, int np)
{
	var->j = 0;
	while (var->token[var->i][var->j])
	{
		if (var->token[var->i][var->j] == '\'')
			ft_compress_ex_tk_aux(var);
		if (var->token[var->i][var->j] == '\"' && var->bool == false)
			var->bool = true;
		else if (var->token[var->i][var->j] == '\"' && var->bool == true)
			var->bool = false;
		ft_compress_extk_swp(var, shell, np);
		if (ft_strlen(var->token[var->i]) <= (size_t)var->j)
			break ;
		if (!var->token[var->i][var->j] || var->token[var->i][var->j] != '$'
			|| !var->token[var->i][var->j + 1])
			var->j++;
	}
}

void	expansive_token(t_shell *shell, char **argv, int np)
{
	t_var	var;

	var.i = 0;
	var.len_exp = 0;
	var.token = argv;
	var.bool = false;
	while (var.token[var.i])
	{
		expansive_token_aux(shell, &var, np);
		var.i++;
	}
	shell->data->lst_process->argv = var.token;
}

void	expansive_token_input(t_shell *shell, char **argv)
{
	t_var	var;

	var.i = 0;
	var.len_exp = 0;
	var.token = argv;
	var.bool = false;
	while (var.token[var.i])
	{
		expansive_token_aux_2(shell, &var);
		var.i++;
	}
}

void	expansive_token_output(t_shell *shell, char **argv)
{
	t_var	var;

	var.i = 0;
	var.len_exp = 0;
	var.token = argv;
	var.bool = false;
	while (var.token[var.i])
	{
		expansive_token_aux_2(shell, &var);
		var.i++;
	}
}
