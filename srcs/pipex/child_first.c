/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:06:26 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/29 10:48:36 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	redirect_input(t_shell *shell)
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

static void	redirect_output(t_shell *shell, t_process *process)
{
	int		fd_out;

	fd_out = fd_output_redirect(shell);
	if (fd_out >= 0)
	{
		dup2(process->fd[WRITE_END], STDOUT_FILENO);
		close(process->fd[WRITE_END]);
		dup2(fd_out, STDOUT_FILENO);
		close (fd_out);
	}
	else
	{
		dup2(process->fd[WRITE_END], STDOUT_FILENO);
		close(process->fd[WRITE_END]);
	}
}

static void	ft_c_i(t_shell *s, t_process *pr, t_process *p_pid)
{
	ft_closer(&p_pid, &pr);
	pr->fd_out = get_fd_builtins(s);
	redirect_input(s);
	redirect_output(s, pr);
}

void	exec_first_child(t_shell *s, t_process *pr, t_process *p_pid)
{
	char	*path;

	if (g_error_code == 1 || g_error_code == 2)
		return ;
	pr->pid = fork();
	if (pr->pid < 0)
		ft_forkerror();
	if (pr->pid == 0)
	{
		ft_c_i(s, pr, p_pid);
		if (pr->fd_out != -2 && start_process(s) == -1)
		{
			if (!pr->argv)
				exit(0);
			get_path(pr->argv[0], (s->data->envpget), &path, s->data->exp_list);
			signal(SIGQUIT, signal_child);
			execve(path, pr->argv, (s->data->envpget));
			if (ft_strlen(pr->argv[0]))
				exit (print_error_cmdo(pr->argv, s));
			exit(127);
		}
		exit(0);
	}
	else
		close(pr->fd[WRITE_END]);
}
