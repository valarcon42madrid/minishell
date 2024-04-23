/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:01:55 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/27 16:22:53 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	ft_error_dir(char *cmd, char **cmdargv, char *cmdcpy)
{
	cmd = ft_protectdot(cmd, cmdargv);
	ft_putstr_fd("42_MiniShell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": is a directory", 2);
	if (*cmdcpy == '.' && !cmdcpy[1])
		return (1);
	else
		return (126);
}

int	ft_error_nosuch(char *cmd, char **cmdargv, char *cmdcpy)
{
	cmd = ft_protectdot(cmd, cmdargv);
	ft_putstr_fd("42_MiniShell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": No such file or directory", 2);
	if (*cmdcpy == '.' && !cmdcpy[1])
		return (1);
	else
		return (127);
}

void	ft_cmd_notfound(char *cmd)
{
	ft_putstr_fd("42_MiniShell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
}

void	print_error_file(char	*file)
{
	ft_putstr_fd("42_MiniShell: No such file or directory: ", 2);
	ft_putendl_fd(file, 2);
}

int	ft_dir(char *arg)
{
	int	i;
	int	x;

	i = 0;
	while (arg[i] && arg[i] == '.')
		i++;
	if (i > 2)
		return (0);
	x = i;
	while (arg[x] && arg[x] == '/')
		x++;
	if (arg[x])
		return (0);
	return (1);
}
