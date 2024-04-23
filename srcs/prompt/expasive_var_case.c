/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasive_var_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:12:45 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 17:59:35 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	expansive_swap_case1(t_shell *shell, t_var *var, int np)
{
	(void)shell;
	if (np == 0)
		var->content = ft_itoa(g_error_code);
	else
		var->content = ft_itoa(0);
	var->before_exp = ft_strndup(var->token[var->i], var->j - 1);
	var->join_befor_tmp = ft_strjoin(var->before_exp, var->content);
	var->after_exp = ft_strjoin(var->join_befor_tmp,
			&var->token[var->i][var->j + var->len_exp]);
	free(var->token[var->i]);
	var->token[var->i] = var->after_exp;
}

void	expansive_swap_case2(t_shell *shell, t_var *var)
{
	var->content = search_env(shell->data->envp_list, var->env);
	var->before_exp = ft_strndup(var->token[var->i], var->j - 1);
	var->join_befor_tmp = ft_strjoin(var->before_exp,
			&var->content[var->len_exp + 1]);
	var->after_exp = ft_strjoin(var->join_befor_tmp,
			&var->token[var->i][var->j + var->len_exp]);
	free(var->token[var->i]);
	var->token[var->i] = var->after_exp;
	var->i = 0;
	var->j = 0;
	var->bool = false;
}

char	*ft_secretpath(t_list *exp_list)
{
	while (exp_list)
	{
		if (!ft_strncmp(exp_list->content, "PATH=", 5))
			return ("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
		exp_list = exp_list->next;
	}
	return (NULL);
}

void	expansive_swap_case3(t_shell *shell, t_var *var)
{
	char	**tmp_matrix;
	char	**split_matrix;
	char	*tmp;
	int		aux;

	var->content = search_env(shell->data->envp_list, var->env);
	if (!*var->content)
	{
		free(var->content);
		if (!ft_vcontent(var, shell))
			return ;
	}
	split_matrix = ft_split(&var->content[var->len_exp + 1], ' ');
	tmp_matrix = matrixjoin(var->token, split_matrix, var->i);
	var->before_exp = ft_strndup(var->token[var->i], var->j - 1);
	var->join_befor_tmp = ft_strjoin(var->before_exp, tmp_matrix[var->i]);
	aux = ft_compress_swp_aux(tmp_matrix, var);
	tmp = tmp_matrix[var->i + aux];
	tmp_matrix[var->i + aux] = ft_strjoin(tmp,
			&var->token[var->i][var->j + var->len_exp]);
	tmp_matrix[var->i] = ft_strjoin(var->before_exp, tmp_matrix[var->i]);
	ft_compresstwo_swp(var, tmp, tmp_matrix, split_matrix);
}

void	expansive_swap(t_shell *shell, t_var *var, int np)
{
	var->j -= var->len_exp;
	var->env = ft_strndup(&var->token[var->i][var->j], var->len_exp);
	if (*var->env == '?' && var->len_exp == 1)
		expansive_swap_case1(shell, var, np);
	else if (var->bool == true)
		expansive_swap_case2(shell, var);
	else
	{
		expansive_swap_case3(shell, var);
	}
	free(var->before_exp);
	free(var->join_befor_tmp);
	free(var->content);
	free(var->env);
}
