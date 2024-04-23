/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:52:32 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/18 20:57:46 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libminishell.h"

static char	*ft_protectcwd(char *cwd, t_data *data)
{
	if (!cwd || !*cwd)
	{
		if (cwd)
			free(cwd);
		return (ft_aux_protect_cwd(data));
	}
	else
		return (cwd);
}

static void	normal_cd(t_data *data)
{
	char	*res;

	res = ft_perfectdir(data);
	if (chdir(res) != 0)
	{
		g_error_code = 1;
		ft_putstr_fd("42_MiniShell: cd: ", 2);
		ft_putstr_fd(data->lst_process->argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free (res);
		return ;
	}
	else
		free (res);
	res = ft_protectcwd(getcwd(0, 0), data);
	update_pwd(data, res);
}

static void	cd_home(t_data *data)
{
	char	*content;
	char	*path;

	content = search_env(data->envp_list, "HOME");
	path = ft_strdup(content + 5);
	free(content);
	if (!path[0])
	{
		ft_putstr_fd("42_MiniShell: cd: HOME not set\n", 2);
		free(path);
		g_error_code = 1;
		return ;
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("42_MiniShell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(path);
		g_error_code = 1;
		return ;
	}
	update_pwd(data, path);
}

void	ft_cd(t_data *data)
{
	if (!data->lst_process->argv[1])
		cd_home(data);
	else
		normal_cd(data);
	g_error_code = 0;
}
