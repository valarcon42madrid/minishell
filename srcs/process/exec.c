/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:00:56 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 13:14:38 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	search_builtins(t_shell *shell)
{
	char	*bcmd;

	if (!shell->data->lst_process->argv)
		return (-1);
	bcmd = *shell->data->lst_process->argv;
	if (!ft_strcmp("cd\0", bcmd))
		return (0);
	if (!ft_strcmp("echo\0", bcmd))
		return (1);
	if (!ft_strcmp("env\0", bcmd))
		return (2);
	if (!ft_strcmp("export\0", bcmd))
		return (3);
	if (!ft_strcmp("pwd\0", bcmd))
		return (4);
	if (!ft_strcmp("unset\0", bcmd))
		return (5);
	if (!ft_strcmp("exit\0", bcmd))
		return (6);
	return (-1);
}

int	start_process(t_shell *shell)
{
	void	(**menu)(t_data *);
	int		opc;
	int		i;

	i = 0;
	opc = 0;
	menu = ft_sec_malloc(sizeof(*menu) * 8);
	menu[0] = &ft_cd;
	menu[1] = &ft_echo;
	menu[2] = &ft_env;
	menu[3] = &ft_export;
	menu[4] = &ft_pwd;
	menu[5] = &ft_unset;
	menu[6] = &ft_exit;
	menu[7] = (void *)0;
	opc = search_builtins(shell);
	if (opc >= 0)
	{
		shell->data->menudir = menu;
		if (shell->data->num_pi == 1 && opc == 6)
			shell->data->shelldir = (void *)shell;
		(*menu[opc])(shell->data);
	}
	free(menu);
	return (opc);
}

char	*ft_protectdot(char	*cmd, char	**cmdargv)
{
	if (cmd[0] == '.' && !cmd[1] && cmdargv[1])
		return (cmdargv[1]);
	else
		return (cmd);
}

static	char	*ft_nonprint(char *str)
{
	int		x;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] < 0)
			str[x] = ' ';
		x++;
	}
	return (str);
}

int	print_error_cmdo(char **cmdargv, t_shell *shell)
{
	int		i;
	int		j;
	char	*cmd;
	char	*cmdcpy;

	i = 0;
	if (!cmdargv)
	{
		ft_putendl_fd("42_MiniShell: : command not found", 2);
		return (127);
	}
	cmdcpy = *cmdargv;
	cmd = ft_nonprint(*cmdargv);
	if (cmd[0] == '.')
	{
		j = ft_error_filename(cmd, cmdargv);
		if (j != 0)
			return (j);
	}
	return (ft_more_error(cmd, cmdargv, cmdcpy, shell));
}
