/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:54:37 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/22 11:17:28 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static char	*ft_secretpwd(t_list	*exp)
{
	char	*aux;
	int		x;

	x = 0;
	while (exp)
	{
		if (!(ft_strncmp(exp->content, "PWD=", 4))
			&& ft_strncmp(exp->content, "\"OLDPWD=", 7))
		{
			aux = (exp->content + 5);
			while (aux[x])
				x++;
			x--;
			while (aux[x] && aux[x] == ' ')
				x--;
			if (aux[x] == '\"')
				aux[x] = '\0';
			return (aux);
		}
		exp = exp->next;
	}
	return (NULL);
}

void	ft_pwd(t_data *data)
{
	char	path[1024];
	char	*ps;

	if (!getcwd(path, sizeof(path)))
	{
		ps = ft_secretpwd(data->exp_list);
		if (!ps)
		{
			g_error_code = 1;
			return ;
		}
		else
		{
			ft_putstr_fd(ps, data->lst_process->fd_out);
			ft_putstr_fd("\n", data->lst_process->fd_out);
			g_error_code = 0;
		}
	}
	else
	{
		ft_putstr_fd(path, data->lst_process->fd_out);
		ft_putstr_fd("\n", data->lst_process->fd_out);
		g_error_code = 0;
	}
}
