/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:40:47 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/24 11:44:05 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	ft_forkerror(void)
{
	g_error_code = 2;
	ft_putstr_fd("42_MiniShell: fork: retry: ", 2);
	ft_putendl_fd("Resource temporarily unavailable", 2);
}

void	redirect_input_exec(t_shell	*shell)
{
	int	fd_file;

	fd_file = fd_input_redirect(shell);
	if (fd_file == -1)
		exit (-1);
	else if (fd_file > 0)
	{
		dup2(fd_file, STDIN_FILENO);
		close(fd_file);
	}
}

void	redirect_output_exec(t_shell *shell)
{
	int	fd_out;

	fd_out = fd_output_redirect(shell);
	if (fd_out >= 0)
	{
		dup2(shell->data->lst_process->fd[WRITE_END], STDOUT_FILENO);
		close(shell->data->lst_process->fd[WRITE_END]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

void	ft_closer(t_process	**process_pid, t_process	**safep)
{
	while (*process_pid)
	{
		if (*safep != (*process_pid)->next)
		{
			close((*process_pid)->fd[READ_END]);
		}
		if (*safep != *process_pid)
		{
			close((*process_pid)->fd[WRITE_END]);
		}
		*process_pid = (*process_pid)->next;
	}
}

void	ft_closerparent(t_process	**process_pid, t_process	**safep)
{
	while (*process_pid)
	{
		close((*process_pid)->fd[WRITE_END]);
		if (*safep != (*process_pid))
		{
			if (ft_strcmp("./minishell", (*process_pid)->argv[0]))
				close((*process_pid)->fd[READ_END]);
		}
		else
			break ;
		*process_pid = ((*process_pid)->next);
	}
}
