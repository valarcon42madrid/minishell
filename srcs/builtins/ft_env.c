/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:53:32 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/22 11:10:16 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	ft_notfill(char	*expenv)
{
	int	x;

	x = 0;
	while (expenv && expenv[x])
	{
		if (expenv[x] == '=')
			return (1);
		x++;
	}
	return (0);
}

static void	ft_errornodir(char	*fn)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(fn, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_error_code = 1;
}

static void	ft_putenv(t_data	*data, t_list	*lst)
{
	if (ft_notfill(lst->content))
	{
		ft_putstr_fd(lst->content, data->lst_process->fd_out);
		ft_putstr_fd("\n", data->lst_process->fd_out);
	}
}

void	ft_env(t_data *data)
{
	t_list	*lst;

	if (!data->envp_list)
	{
		g_error_code = 1;
		return ;
	}
	if (data->lst_process->argv[1])
	{
		ft_errornodir(data->lst_process->argv[1]);
		return ;
	}
	lst = data->envp_list;
	while (lst->next)
	{
		ft_putenv(data, lst);
		lst = lst->next;
	}
	if (ft_notfill(lst->content))
	{
		ft_putstr_fd(lst->content, data->lst_process->fd_out);
		ft_putstr_fd("\n", data->lst_process->fd_out);
	}
	g_error_code = 0;
}
