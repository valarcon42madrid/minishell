/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:38:15 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 13:13:15 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static int	ft_adresserror(char **cmdargv)
{
	if (cmdargv[1] && (ft_strcmp("echo", cmdargv[1]) == '\0'
			|| ft_strcmp("ls", cmdargv[1]) == '\0'
			|| ft_strcmp("pwd", cmdargv[1]) == '\0'
			|| ft_strcmp("env", cmdargv[1]) == '\0'
			|| ft_strcmp("as", cmdargv[1]) == '\0'
			|| ft_strcmp("grep", cmdargv[1]) == '\0'
			|| ft_strcmp("cat", cmdargv[1]) == '\0'
			|| ft_strcmp("cut", cmdargv[1]) == '\0'
			|| ft_strcmp("make", cmdargv[1]) == '\0'
			|| ft_strcmp("awk", cmdargv[1]) == '\0'
			|| ft_strcmp("./minishell", cmdargv[1]) == '\0'))
		return (1);
	else
		return (0);
}

int	ft_error_filename(char *cmd, char **cmdargv)
{
	int	j;

	j = 1;
	while (cmd[j] && cmd[j] == ' ')
		j++;
	if (!cmd[j] && !cmdargv[1])
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": filename argument required\n", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": usage: . filename [arguments]", 2);
		return (2);
	}
	if (ft_adresserror(cmdargv))
	{
		ft_putendl_fd("42_MiniShell: ����: command not found", 2);
		return (127);
	}
	return (0);
}

static int	ft_nosuchdir(char	*arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_notpath(t_list	*exp_l)
{
	char	*aux;

	while (exp_l)
	{
		if (!ft_strncmp(exp_l->content, "PATH=\"\"", 7))
		{
			aux = exp_l->content;
			if (!aux[8])
				return (1);
		}
		else if (!ft_strncmp(exp_l->content, "PATH=\"", 6))
			return (0);
		exp_l = exp_l->next;
	}
	return (1);
}

int	ft_more_error(char *cmd, char **cmdargv, char *cmdcpy, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i] && cmd[i] == '.')
		i++;
	if (cmd[i] == '/' || (!cmd[i] && i < 2) || !access(*cmdargv, F_OK))
	{
		j = i;
		while (cmd[i] && cmd[i] == '/')
			i++;
		if (((!cmd[i]) && j < 3 && (!cmdargv[1]
					|| ft_dir(cmdargv[1]))) || !access(*cmdargv, F_OK))
			return (ft_error_dir(cmd, cmdargv, cmdcpy));
		else if (access(cmd, F_OK))
			return (ft_error_nosuch(cmd, cmdargv, cmdcpy));
	}
	else if (ft_nosuchdir(cmd) == 1 || ft_notpath(shell->data->exp_list))
		return (ft_error_nosuch(cmd, cmdargv, cmdcpy));
	else
		ft_cmd_notfound(cmd);
	return (127);
}
