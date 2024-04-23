/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:23:58 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/18 21:08:01 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libminishell.h"

char	*ft_aux_pwd(t_data	*data)
{
	int		y;
	int		x;
	char	*res;

	y = 0;
	res = ft_aux_aux_pwd(data);
	x = ft_strlen(res) - 1;
	if (res[x] && res[x] == '\"')
		res[x] = '\0';
	while (res[--x] && (res[x] == '.' || res[x] == '/'))
	{
		if (res[x] == '/')
			y++;
		res[x] = '\0';
	}
	while (y != 0 && res[x])
	{
		if (res[x] == '/')
			y--;
		res[x--] = '\0';
	}
	return (res);
}

char	*ft_oldwithpwd(char	*tmp, char	*res, t_data	*data)
{
	free(tmp);
	tmp = ft_strjoin("OLD", res);
	replace_content_envp(data, tmp, "OLDPWD");
	return (tmp);
}

char	*ft_aux_aux_pwd(t_data	*data)
{
	char	*res;
	char	*tmp;

	res = search_env(data->exp_list, "PWD");
	tmp = ft_strdup(&(res[5]));
	free(res);
	res = ft_strjoin("PWD=", tmp);
	free(tmp);
	return (res);
}

char	*ft_aux_aux_pc(t_data	*data)
{
	char	*aux;
	char	*res;
	int		x;
	int		y;

	y = 0;
	aux = search_env(data->exp_list, "PWD");
	res = ft_strdup(&(aux[5]));
	free(aux);
	x = ft_strlen(res) - 1;
	if (res[x] == '\"')
		res[x--] = '\0';
	while (res[x] && (res[x] == '.' || res[x] == '/'))
	{
		if (res[x] == '/')
			y++;
		res[x--] = '\0';
	}
	while (y != 0 && res[x])
	{
		if (res[x] == '/')
			y--;
		res[x--] = '\0';
	}
	return (res);
}

char	*ft_aux_protect_cwd(t_data	*data)
{
	char	*aux;
	char	*res;

	aux = search_env(data->envp_list, "PWD");
	if (!*aux)
	{
		free(aux);
		res = ft_aux_aux_pc(data);
	}
	else
	{
		res = ft_strdup(&(aux[4]));
		free(aux);
	}
	return (res);
}
