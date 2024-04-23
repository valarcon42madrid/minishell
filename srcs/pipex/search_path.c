/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:10:32 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/28 10:36:33 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static void	loop(char **paths, char *cmd, char **f_path)
{
	char	*path_cmd;
	char	*path;
	int		index;
	int		fd;

	index = 0;
	path = 0;
	while (paths[index])
	{
		path = ft_strjoin(paths[index], "/");
		path_cmd = ft_strjoin(path, cmd);
		free(path);
		fd = open(path_cmd, O_RDONLY);
		if (fd >= 0)
		{
			*f_path = path_cmd;
			free_matrix(paths);
			close(fd);
			return ;
		}
		free(path_cmd);
		index++;
	}
}

char	*mini_path(char *envp[], t_list	*exp_list)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (ft_secretpath(exp_list));
}

void	get_path(char *cmd, char *envp[], char **f_path, t_list *exp_list)
{
	char	**paths;
	int		fd;

	if (*cmd == '.' || *cmd == '/')
	{
		fd = open(cmd, O_RDONLY);
		if (fd >= 0)
		{
			*f_path = ft_strdup(cmd);
			close (fd);
			return ;
		}
	}
	if (!mini_path(envp, exp_list))
	{
		*f_path = NULL;
		return ;
	}
	paths = ft_mypath(envp, exp_list, f_path);
	if (!paths)
		return ;
	else
		loop(paths, cmd, f_path);
}

char	**split_cmd_arg(char *argv)
{
	char	**cmd_arg;

	cmd_arg = ft_split(argv, ' ');
	return (cmd_arg);
}
