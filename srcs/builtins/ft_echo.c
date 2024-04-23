/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:53:21 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 10:45:54 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	print_args(t_data *data, int *index)
{
	while (data->lst_process->argv[*index])
	{
		if (data->lst_process->argv[*index + 1])
		{
			ft_putstr_fd(data->lst_process->argv[*index],
				data->lst_process->fd_out);
			if (ft_strcmp(data->lst_process->argv[*index], " ")
				&& ft_strcmp(data->lst_process->argv[*index], ""))
				ft_putstr_fd(" ", data->lst_process->fd_out);
		}
		else
			ft_putstr_fd(data->lst_process->argv[*index],
				data->lst_process->fd_out);
		(*index)++;
	}
}

static int	check_argument(char *content)
{
	int	hyphen;
	int	n;

	hyphen = 0;
	n = 0;
	while (*content)
	{
		if (*content == '-')
			hyphen++;
		else if (*content != 'n')
			n = -1;
		content++;
	}
	if (hyphen == 1 && !n)
		return (1);
	return (0);
}

static void	check_flag(t_data *data, int *index, int *flag)
{
	while (data->lst_process->argv[*index])
	{
		if (!check_argument(data->lst_process->argv[*index]))
			return ;
		(*index)++;
		*flag = 1;
	}
}

void	ft_echo(t_data *data)
{
	int	flag;
	int	index;

	flag = 0;
	index = 1;
	if (!data->lst_process->argv[index])
	{
		ft_putstr_fd("\n", data->lst_process->fd_out);
		return ;
	}
	check_flag(data, &index, &flag);
	print_args(data, &index);
	if (!flag)
		ft_putstr_fd("\n", data->lst_process->fd_out);
	g_error_code = 0;
}
