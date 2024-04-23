/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:54:51 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/22 11:18:47 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static int	invalid_arg(t_data *data, char *arg)
{
	(void)data;
	if (ft_strchr(arg, '=') || !check_arg_name(arg))
	{
		not_valid_identifier("unset", arg);
		g_error_code = 1;
		return (1);
	}
	return (0);
}

static void	unset_arg(t_data *data, char *arg)
{
	char	*envp_var;
	char	*exp_var;

	envp_var = search_env(data->envp_list, arg);
	exp_var = search_env(data->exp_list, arg);
	if (envp_var)
		ft_lstdelone(&data->envp_list, (void *)envp_var);
	if (exp_var && ft_strncmp("PWD=", exp_var, 4)
		&& ft_strncmp("OLDPWD=", exp_var, 7))
		ft_lstdelone(&data->exp_list, (void *)exp_var);
	free(envp_var);
	free(exp_var);
}

void	ft_unset(t_data *data)
{
	int	index;

	index = 1;
	if (!data->lst_process->argv[index])
	{
		g_error_code = 0;
		return ;
	}
	while (data->lst_process->argv[index])
	{
		if (invalid_arg(data, data->lst_process->argv[index]))
			return ;
		unset_arg(data, data->lst_process->argv[index]);
		index++;
	}
	g_error_code = 0;
}
