/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:11:16 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/18 17:27:12 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static int	imput_redirect_aux(t_redirect *input, int *fd)
{
	if (get_num_words(input->file) >= 2)
	{
		ft_putstr_fd("42_MiniShell: ambiguous redirect\n", 2);
		return (-1);
	}
	*fd = open(input->file[0], O_RDONLY);
	if (*fd == -1)
	{
		print_error_file(input->file[0]);
		return (-1);
	}
	return (0);
}

int	fd_input_redirect(t_shell *shell)
{
	t_redirect	*input;
	int			fd;

	fd = 0;
	input = shell->data->lst_process->input;
	while (input)
	{
		if (!ft_strcmp(input->symbol, "<\0"))
			if (imput_redirect_aux(input, &fd) == -1)
				return (-1);
		if (!ft_strcmp(input->symbol, "<<\0"))
		{
			fd = shell->data->lst_process->input->pos;
			if (fd != -1)
				return (fd);
		}
		input = input->next;
		if (input)
			close(fd);
	}
	return (fd);
}

static int	output_redirect_aux(t_redirect *output, int *fd)
{
	DIR	*dir;

	dir = opendir(output->file[0]);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("42_MiniShell: ", 2);
		ft_putstr_fd(*output->file, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (-2);
	}
	*fd = open(output->file[0], O_WRONLY | O_CREAT | O_TRUNC | O_APPEND,
			S_IRWXU);
	return (0);
}

int	fd_output_redirect(t_shell *shell)
{
	t_redirect	*output;
	int			fd;

	fd = -1;
	output = shell->data->lst_process->output;
	while (output)
	{
		if (get_num_words(output->file) >= 2 || !*output->file[0])
		{
			ft_putstr_fd("42_MiniShell: ambiguous redirect\n", 2);
			return (-2);
		}
		if (!ft_strcmp(output->symbol, ">\0"))
			if (output_redirect_aux(output, &fd) == -2)
				return (-2);
		if (!ft_strcmp(output->symbol, ">>\0"))
			fd = open(output->file[0], O_WRONLY | O_CREAT | O_APPEND,
					S_IRWXU);
		output = output->next;
		if (output)
			close(fd);
	}
	return (fd);
}
