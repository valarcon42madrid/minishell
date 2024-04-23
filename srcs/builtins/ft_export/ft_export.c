/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:51:35 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/22 11:20:53 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libminishell.h"

static void	print_export_list(t_data *data)
{
	t_list		*lst;
	static int	first = 0;
	char		*tmp;

	lst = data->exp_list;
	if (first)
	{
		tmp = search_env(data->exp_list, "_");
		if (tmp[0])
			ft_lstdelone(&data->exp_list, tmp);
		free(tmp);
	}
	while (lst)
	{
		ft_putstr_fd("declare -x ", data->lst_process->fd_out);
		ft_putstr_fd(lst->content, data->lst_process->fd_out);
		ft_putstr_fd("\n", data->lst_process->fd_out);
		lst = lst->next;
	}
	first = 1;
}

static void	envp_part(t_data *data, char *var)
{
	char	*name;

	name = get_name(var);
	if (already_exist(data->envp_list, var))
	{
		if (ft_strchr(var, '='))
			replace_content_envp(data, var, name);
	}
	else
		if (ft_strchr(var, '='))
			ft_lstadd_back(&(data->envp_list), ft_lstnew(ft_strdup(var)));
	free(name);
}

static void	check_var_list(t_data *data, char *var, char *name)
{
	char	*tmp;

	tmp = 0;
	if (!data->tmp_var_list)
		ft_lstadd_back(&(data->exp_list), ft_lstnew(ft_strdup(var)));
	else
	{
		tmp = search_env(data->tmp_var_list, name);
		if (*tmp)
		{
			ft_lstadd_back(&(data->envp_list), ft_lstnew(ft_strdup(tmp)));
			ft_lstadd_back(&(data->exp_list),
				ft_lstnew(fill_with_dquotes(tmp)));
			ft_lstdelone(&data->tmp_var_list, tmp);
		}
		else
			ft_lstadd_back(&(data->exp_list), ft_lstnew(ft_strdup(var)));
	}
	free(tmp);
}

static void	exp_part(t_data *data, char *var)
{
	char	*name;

	name = get_name(var);
	if (already_exist(data->exp_list, var))
	{
		if (ft_strchr(var, '='))
			replace_content_exp(data, fill_with_dquotes(var), name);
	}
	else
	{
		if (ft_strchr(var, '='))
			ft_lstadd_back(&(data->exp_list),
				ft_lstnew(fill_with_dquotes(var)));
		else
			check_var_list(data, var, name);
	}
	free(name);
}

void	ft_export(t_data *data)
{
	int	index;

	if (!data->lst_process->argv[1])
	{
		print_export_list(data);
		return ;
	}
	index = 1;
	while (data->lst_process->argv[index])
	{
		if (!check_arg_name(data->lst_process->argv[index]))
		{
			not_valid_identifier("export", data->lst_process->argv[index]);
			g_error_code = 1;
			return ;
		}
		envp_part(data, data->lst_process->argv[index]);
		if (ft_strncmp(data->lst_process->argv[1], "PWD=", 4)
			&& ft_strncmp(data->lst_process->argv[1], "OLDPWD=", 7))
			exp_part(data, data->lst_process->argv[index]);
		index++;
	}
	sort_env_list(data->exp_list);
	g_error_code = 0;
}
