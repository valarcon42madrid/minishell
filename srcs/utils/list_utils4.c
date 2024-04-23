/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:29:17 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/26 13:12:39 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

static char	*ft_nextshlvl(char *shlvl)
{
	int		lvl;
	char	*result;

	result = ft_strdup("SHLVL=1");
	if (!shlvl || ft_strlen(shlvl) < 6)
		return (result);
	if (!shlvl[6] || ft_text(&(shlvl[6])))
		return (result);
	else
	{
		free(result);
		lvl = ft_atoi(&(shlvl[6]));
		lvl++;
		result = ft_strjoin("SHLVL=", ft_itoa(lvl));
	}
	return (result);
}

void	ft_shlvlnext(char **envp, int index, t_list	*envp_list)
{
	char	*envpaux;

	envpaux = ft_nextshlvl(envp[index]);
	ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup(envpaux)));
	free(envpaux);
}

void	ft_pwd_add(t_list	*envp_list)
{
	char	*envpaux;

	envpaux = getcwd(0, 0);
	if (!envpaux)
		envpaux = ft_strdup("");
	ft_lstadd_back(&envp_list, ft_lstnew(ft_strjoin("PWD=", envpaux)));
	free(envpaux);
}

int	ft_is_shlvl(char **envp)
{
	while (*envp)
	{
		if ((*envp)[0] && (*envp)[1] && (*envp)[2]
			&& (*envp)[3] && (*envp)[4] && (*envp)[5])
		{
			if ((*envp)[0] == 'S' && (*envp)[1] == 'H'
				&& (*envp)[2] == 'L' && (*envp)[3] == 'V' && (*envp)[4] == 'L'
				&& (*envp)[5] == '=')
				return (1);
		}
		envp++;
	}
	return (0);
}

int	ft_is_cm(char **envp)
{
	while (*envp)
	{
		if ((*envp)[0] && (*envp)[1])
		{
			if ((*envp)[0] == '_' && (*envp)[1] == '=')
				return (1);
		}
		envp++;
	}
	return (0);
}
