/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:59:27 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 17:38:05 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

t_shell	*init_minishell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)ft_sec_malloc(sizeof(t_shell));
	shell->data = (t_data *)ft_sec_malloc(sizeof(t_data));
	shell->status = false;
	shell->data->envp_list = fill_envp_list(envp);
	shell->data->exp_list = fill_exp_list(envp);
	shell->data->tmp_var_list = NULL;
	shell->data->num_p = 0;
	shell->data->num_pi = 0;
	g_error_code = 0;
	sort_env_list(shell->data->exp_list);
	fill_slung_dash(shell->data);
	shell->data->envpget = NULL;
	shell->data->shelldir = NULL;
	shell->data->line = NULL;
	shell->data->menudir = NULL;
	return (shell);
}

void	init_fd_redirect(t_shell *shell)
{
	assign_fd_to_process(shell->data->lst_process);
	if (shell->data->lst_process->input)
		loop_expa_redirect_input(shell, shell->data->lst_process->input);
	if (shell->data->lst_process->output)
		loop_expa_redirect_output(shell, shell->data->lst_process->output);
}

static void	init_process(t_shell *shell, int num_process)
{
	int	i;

	i = 0;
	while (i < num_process)
	{	
		expansive_token(shell, shell->data->lst_process->argv, i);
		del_quotes(shell->data->lst_process);
		shell->data->lst_process = shell->data->lst_process->next;
		i++;
	}
}

void	start_parseo(t_shell *shell, char *line)
{
	t_process	*process;
	int			num_process;

	num_process = 0;
	if (line && *line)
	{
		if (pre_parse(line) == false)
			ft_sytax_error();
		else
		{
			num_process = get_process(shell->data, line);
			if (num_process > 0)
			{
				init_fd_redirect(shell);
				process = shell->data->lst_process;
				init_process(shell, num_process);
				shell->data->lst_process = process;
				start_pipe(shell, &num_process, line);
				shell->data->lst_process = process;
			}
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_shell		*shell;
	char		*line;

	if (!envp || !*envp)
		shell = ft_init_no_env();
	else
		shell = init_minishell(envp);
	ft_fix_var(argv, argc);
	while (1)
	{
		shell->data->lst_process = NULL;
		signals();
		line = prompt(shell);
		add_history(line);
		line = ft_justquotes(line);
		start_parseo(shell, line);
		free_resources(shell->data->lst_process);
		if (!line)
			ft_preemfree(shell);
		free(line);
	}
	return (0);
}
