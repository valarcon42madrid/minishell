/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:54:18 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/29 12:06:22 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	not_numeric_arg(t_data *data)
{
	ft_putstr_fd("42_MiniShell: exit: ", 2);
	ft_putstr_fd(data->lst_process->argv[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_putstr_fd("exit\n", 2);
}

static void	ft_freeend(t_shell *shell, t_data *data)
{
	if (data->menudir)
		free (data->menudir);
	if (shell && shell->data && shell->data->num_pi == 1)
	{
		if (shell->data->line)
			free (shell->data->line);
		if (shell->data->envpget)
			free (shell->data->envpget);
		free_resources(shell->data->lst_process);
		free (shell->data);
		free (shell);
	}
}

static int	ft_exiter(t_data	*data)
{
	ft_putstr_fd("exit\n", 2);
	g_error_code = 0;
	ft_freeend((t_shell *)data->shelldir, data);
	return (0);
}

static void	ft_arg_exit(t_data	*data)
{
	int	aux;

	ft_putstr_fd("exit\n", STDIN_FILENO);
	aux = (min_atoi(data->lst_process->argv[1]));
	ft_freeend((t_shell *)data->shelldir, data);
	exit(aux);
}

void	ft_exit(t_data *data)
{
	if (!data->lst_process->argv[1])
	{
		ft_putstr_fd("exit\n", STDIN_FILENO);
		ft_freeend((t_shell *)data->shelldir, data);
		exit(0);
	}
	if (min_atoi(data->lst_process->argv[1]) == -1)
	{
		not_numeric_arg(data);
		ft_freeend((t_shell *)data->shelldir, data);
		exit(255);
	}
	if (get_num_words_join(data->lst_process->argv) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("42_MiniShell: exit: too many arguments\n", 2);
		g_error_code = 1;
		return ;
	}
	if (data->lst_process->argv[1])
		ft_arg_exit(data);
	exit(ft_exiter(data));
}
