/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:55:17 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/28 18:34:48 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	free_shell_data(t_shell *shell)
{
	free(shell->data);
	free(shell);
}

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	free_redirect(t_redirect *redirect)
{
	t_redirect	*tmp;

	while (redirect)
	{
		if (redirect->file[0])
		{
			free (redirect->file[0]);
			free (redirect->file[1]);
			free (redirect->file);
		}
		free(redirect->symbol);
		tmp = redirect->next;
		free(redirect);
		redirect = tmp;
	}
}

void	free_resources(t_process *process)
{
	t_process	*tmp;

	while (process)
	{
		if (process->argv)
			free_matrix(process->argv);
		free_redirect(process->input);
		free_redirect(process->output);
		if (process->fd)
		{
			close(process->fd[0]);
			close(process->fd[1]);
			free(process->fd);
		}
		if (process->fd_out > 2)
			close(process->fd_out);
		tmp = process->next;
		free(process);
		process = tmp;
	}
	unlink(".tmp");
}
