/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:09:24 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 13:26:27 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	init_all_pipe(t_shell *shell)
{
	t_process	*process;

	process = shell->data->lst_process;
	g_error_code = 137;
	while (process)
	{
		pipe(process->fd);
		if (process->input && process->input->pos)
			process->input->pos = ft_input_heredoc(process);
		process = process->next;
	}
	signals();
}

static void	ft_closeallread(t_process *process_pid)
{
	while (process_pid)
	{
		if (ft_strcmp("./minishell", (process_pid)->argv[0]))
			close (process_pid->fd[READ_END]);
		process_pid = process_pid->next;
	}
}

static void	aux_start_pipe(t_shell *shell, t_process *process,
	t_process *process_pid)
{
	shell->data->lst_process = process->next;
	exec_final_child(shell, process->next, process->fd, process_pid);
	ft_closeallread(process_pid);
	if (g_error_code != 1 && g_error_code != 2)
		start_pipe2(shell, process, process_pid);
	if (!ft_strcmp("", shell->data->lst_process->argv[0]))
		g_error_code = 0;
}

static void	ft_onechild_gestor(t_process *process, t_shell *shell, char *line)
{
	g_error_code = 137;
	if (process->input && process->input->pos)
		process->input->pos = ft_input_heredoc(process);
	signals();
	shell->data->line = line;
	exec_only_one_process(shell);
	if (!ft_strcmp("", process->argv[0]))
		g_error_code = 0;
	shell->data->line = NULL;
}

void	start_pipe(t_shell *shell, int *num_p, char *line)
{
	t_process	*process;
	t_process	*process_pid;

	process_pid = shell->data->lst_process;
	shell->status = true;
	process = shell->data->lst_process;
	shell->data->envpget = get_env(shell->data);
	if (*num_p == 1)
	{
		ft_onechild_gestor(process, shell, line);
		return ;
	}
	else if (*num_p > 1)
	{
		init_all_pipe(shell);
		exec_first_child(shell, process, process_pid);
		while (*num_p > 2)
		{
			shell->data->lst_process = process->next;
			exect_b_childs(shell, process->next, process->fd, process_pid);
			process = process->next;
			(*num_p)--;
		}
		aux_start_pipe(shell, process, process_pid);
	}
}
