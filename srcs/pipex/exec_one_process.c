/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:04:25 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/18 18:27:20 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	wait_for_child(t_shell *shell)
{
	int	status;

	waitpid(shell->data->lst_process->pid, &status, 0);
	if (status == 2)
		g_error_code = 130;
	if (status == 3)
		g_error_code = 131;
	if (WIFEXITED(status))
		g_error_code = WEXITSTATUS(status);
}

static void	close_parent_fd(t_shell *shell)
{
	if (shell->data->lst_process->pid > 0)
	{
		signal(SIGQUIT, signal_child);
		signal(SIGINT, signal_child);
		close(shell->data->lst_process->fd[WRITE_END]);
		close(shell->data->lst_process->fd[READ_END]);
		wait_for_child(shell);
	}
}

static void	ft_ifcloseout(t_shell *shell)
{
	if (shell->data->lst_process->fd_out > 2)
		close(shell->data->lst_process->fd_out);
}

static void	ft_iforkfail(t_shell *shell)
{
	if (shell->data->lst_process->pid < 0)
		ft_forkerror();
}

void	exec_only_one_process(t_shell *shell)
{
	char	*path;

	if (g_error_code == 1)
		return ;
	shell->data->lst_process->fd_out = get_fd_builtins(shell);
	if (shell->data->lst_process->fd_out != -2 && start_process(shell) == -1)
	{
		ft_ifcloseout(shell);
		shell->data->lst_process->pid = fork();
		ft_iforkfail(shell);
		if (shell->data->lst_process->pid == 0)
		{
			redirect_io(shell);
			if (!shell->data->lst_process->argv)
				exit(print_error_cmdo(shell->data->lst_process->argv, shell));
			get_path(shell->data->lst_process->argv[0], (shell->data->envpget),
				&path, shell->data->exp_list);
			signal(SIGQUIT, SIG_DFL);
			execve(path, shell->data->lst_process->argv, shell->data->envpget);
			if (ft_strlen(shell->data->lst_process->argv[0]))
				exit(print_error_cmdo(shell->data->lst_process->argv, shell));
			exit(127);
		}
		close_parent_fd(shell);
	}
}
