/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:52:16 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/12 19:41:44 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	ft_add_pwd_e(t_shell *shell, t_var	*var)
{
	int		x;
	char	*res;
	char	*tmp;

	x = 0;
	res = search_env(shell->data->exp_list, "PWD");
	tmp = ft_strdup(&(res[5]));
	free(res);
	res = ft_strjoin("PWD=", tmp);
	free(tmp);
	while (res[x])
		x++;
	x--;
	if (res[x] && res[x] == '\"')
		res[x] = '\0';
	x--;
	var->content = ft_strdup(res);
	free(res);
}

void	ft_add_oldpwd_e(t_shell *shell, t_var	*var)
{
	int		x;
	char	*res;
	char	*tmp;

	x = 0;
	res = search_env(shell->data->exp_list, "OLDPWD");
	tmp = ft_strdup(&(res[8]));
	free(res);
	res = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	while (res[x])
		x++;
	x--;
	if (res[x] && res[x] == '\"')
		res[x] = '\0';
	x--;
	var->content = ft_strdup(res);
	free(res);
}

static	int	ft_ex_sw_c2_null(t_shell	*shell, t_var	*var)
{
	expansive_swap_case2(shell, var);
	return (0);
}

int	ft_vcontent(t_var	*var, t_shell	*shell)
{
	if (!ft_strcmp(var->env, "PATH"))
	{
		if (ft_secretpath(shell->data->exp_list))
			var->content = ft_strdup(ft_secretpath(shell->data->exp_list));
		else
			return (ft_ex_sw_c2_null(shell, var));
		if (!var->content || !*var->content)
			return (ft_ex_sw_c2_null(shell, var));
	}
	else if (!ft_strcmp(var->env, "OLDPWD"))
		ft_add_oldpwd_e(shell, var);
	else if (!ft_strcmp(var->env, "PWD"))
		ft_add_pwd_e(shell, var);
	else
		return (ft_ex_sw_c2_null(shell, var));
	return (1);
}

void	ft_add_var(t_var	*var)
{
	(*var).aux = (*var).tmp_join;
	(*var).tmp_join = ft_strjoin((*var).tmp_join, (*var).tmp[(*var).j]);
	free((*var).aux);
	free((*var).tmp[(*var).j++]);
}
