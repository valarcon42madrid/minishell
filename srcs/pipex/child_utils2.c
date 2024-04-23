/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:45:02 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/18 17:34:43 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	ft_parent_hd(pid_t	pd, int fd)
{
	int	status;

	waitpid(pd, &status, 0);
	close (fd);
	if (WIFEXITED(status))
		g_error_code = WEXITSTATUS(status);
	if (status == 256)
		g_error_code = 1;
	if (status == 0)
		g_error_code = 0;
}

static void	ft_child_hd(t_redirect	*input, int fd)
{
	char	*tmp;

	signal(SIGQUIT, exit);
	signal(SIGINT, sig_hd);
	tmp = NULL;
	tmp = readline("> ");
	if (g_error_code == 1)
		exit(1);
	if (tmp && ft_strcmp(tmp, input->file[0]))
		ft_putendl_fd(tmp, fd);
	while (tmp && ft_strcmp(tmp, input->file[0]))
	{
		free(tmp);
		tmp = readline("> ");
		if (tmp && !*tmp && g_error_code == 1)
			exit(512);
		if (tmp && ft_strcmp(tmp, input->file[0]))
			ft_putendl_fd(tmp, fd);
	}
	free(tmp);
	close (STDIN_FILENO);
	close (STDOUT_FILENO);
	exit (0);
}

int	fd_input_eof(t_redirect *input)
{
	int		fd;
	pid_t	pd;

	fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC | O_APPEND,
			S_IRWXU);
	if (g_error_code != 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		pd = fork();
	}
	else
		pd = -1;
	if (pd == 0)
		ft_child_hd(input, fd);
	else if (pd == -1)
		return (-1);
	else
	{
		ft_parent_hd(pd, fd);
		if (g_error_code != 1)
			return (fd);
	}
	return (-1);
}

int	ft_input_heredoc(t_process *process)
{
	t_redirect	*input;
	int			fd;

	input = process->input;
	fd = process->fd[0];
	while (input)
	{
		if (!ft_strcmp(input->symbol, "<<\0"))
		{
			fd = fd_input_eof(input);
			close (fd);
			fd = ft_fd_valid(fd);
		}
		input = input->next;
		if (input)
		{
			close(fd);
			fd = -1;
		}
	}
	return (fd);
}

void	start_pipe2(t_shell *shell, t_process *process, t_process *pro_pid)
{
	(void)shell;
	while (pro_pid)
	{
		waitpid(pro_pid->pid, &pro_pid->status, 0);
		if (pro_pid->status == 2)
			g_error_code = 130;
		if (pro_pid->status == 3)
			g_error_code = 131;
		pro_pid = pro_pid->next;
	}
	if (WIFEXITED(process->next->status))
	{
		if (WEXITSTATUS(process->next->status) == 255)
			g_error_code = 127;
		else
			g_error_code = WEXITSTATUS(process->next->status);
	}
}
