/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:19:36 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/18 21:08:03 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libminishell.h"

char	*ft_purepwd(t_data	*data)
{
	char	*tmp;

	tmp = search_env(data->envp_list, "PWD");
	if (!*tmp)
	{
		free(tmp);
		tmp = ft_aux_pwd(data);
	}
	return (tmp);
}

void	update_pwd(t_data *data, char *new_pwd)
{
	char	*tmp;
	char	*pwd;
	char	*old_pwd;
	DIR		*directory;

	directory = opendir(new_pwd);
	tmp = ft_purepwd(data);
	old_pwd = ft_strjoin("OLD", tmp);
	free(tmp);
	ft_updateoldpwd(data, old_pwd);
	replace_content_exp(data, fill_with_dquotes(old_pwd), "OLDPWD");
	if (directory == NULL)
		new_pwd = ft_errorcwd(old_pwd);
	else
		closedir(directory);
	free(old_pwd);
	pwd = ft_strjoin("PWD=", new_pwd);
	tmp = search_env(data->envp_list, "PWD");
	if (*tmp)
		replace_content_envp(data, pwd, "PWD");
	replace_content_exp(data, fill_with_dquotes(pwd), "PWD");
	free(tmp);
	free(pwd);
	if (new_pwd)
		free(new_pwd);
}

void	ft_updateoldpwd(t_data	*data, char	*old_pwd)
{
	char	*tmp;
	char	*res;

	tmp = search_env(data->envp_list, "OLDPWD");
	if (*tmp)
	{
		res = search_env(data->envp_list, "PWD");
		if (*res)
			tmp = ft_oldwithpwd(tmp, res, data);
		else
		{
			free(res);
			res = search_env(data->envp_list, "OLDPWD=");
			if (*res)
				replace_content_envp(data, old_pwd, "OLDPWD");
			else
			{
				free (res);
				res = ft_strdup("OLDPWD=");
				replace_content_envp(data, res, "OLDPWD");
			}
		}
		free(res);
	}
	free(tmp);
}

char	*ft_errorcwd(char	*old_pwd)
{
	ft_putstr_fd("cd: error retrieving current directory: getcwd: ", 2);
	ft_putstr_fd("cannot access parent directories: ", 2);
	ft_putstr_fd("No such file or directory\n", 2);
	g_error_code = 0;
	return (ft_strjoin(&(old_pwd[7]), "/.."));
}

char	*ft_perfectdir(t_data	*data)
{
	DIR		*directory;
	char	*res;

	res = ft_strdup(data->lst_process->argv[1]);
	directory = opendir(data->lst_process->argv[1]);
	if (directory != NULL)
		closedir(directory);
	else
		return (ft_errorcwd(ft_strjoin("OLD", ft_purepwd(data))));
	return (res);
}
