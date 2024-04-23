/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 12:23:28 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/24 13:15:37 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	ft_fd_valid(int fd)
{
	if (fd != -1)
		fd = open(".tmp", O_RDONLY);
	else
	{
		fd = open(".tmp", O_RDONLY);
		close (fd);
		fd = -1;
	}
	return (fd);
}

char	**ft_mypath(char	*envp[], t_list	*exp_list, char	**f_path)
{
	char	**paths;

	paths = ft_split(ft_strchr(mini_path(envp, exp_list), '/'), ':');
	if (!paths || !*paths)
	{
		*f_path = NULL;
		if (paths)
			free (paths);
		paths = NULL;
	}
	else if (!paths[1])
	{
		ft_putstr_fd("job-working-directory: ", 2);
		ft_putstr_fd("error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	return (paths);
}
