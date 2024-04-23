/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:55:53 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/26 15:57:09 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

char	*search_env(t_list *envp_list, char *name)
{
	t_list	*lst;
	int		name_len;
	int		x;

	x = 0;
	lst = envp_list;
	name_len = get_var_len(name);
	while (name && name[x] && name[x] != '=')
		x++;
	if (name[x] == '=')
		x = 1;
	else
		x = 0;
	while (lst)
	{
		if (name_len == get_var_len(lst->content))
		{
			if (!ft_strncmp(lst->content, name, name_len + x))
				return (ft_strdup(lst->content));
		}
		lst = lst->next;
	}
	return (ft_strdup(""));
}

static void	swap(t_list *a, t_list *b)
{
	t_list	aux;

	aux.content = b->content;
	b->content = a->content;
	a->content = aux.content;
}

void	sort_env_list(t_list *lst)
{
	t_list	*pt;
	t_list	*lptr;
	int		swapped;

	lptr = 0;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		pt = lst;
		while (pt->next != lptr)
		{
			if (ft_strcmp((char *)pt->content, (char *)pt->next->content) > 0)
			{
				swap(pt, pt->next);
				swapped = 1;
			}
			pt = pt->next;
		}
		lptr = pt;
	}
}

int	ft_text(char *sh)
{
	int	i;

	i = 0;
	while (sh[i])
	{
		if (!sh[i])
			return (0);
		else if (sh[i] > '9' || sh[i] < '0')
			return (1);
		else
			i++;
	}
	return (0);
}

t_list	*fill_envp_list(char **envp)
{
	int		index;
	t_list	*envp_list;

	index = 0;
	envp_list = ft_lstnew(ft_strdup(envp[index]));
	index++;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "SHLVL=", 6) == 0)
			ft_shlvlnext(envp, index, envp_list);
		else if (ft_strncmp(envp[index], "OLDPWD", 6))
			ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup(envp[index])));
		else
			ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup("OLDPWD")));
		index++;
	}
	if (!ft_ispwd(envp))
		ft_pwd_add(envp_list);
	if (!ft_isoldpwd(envp))
		ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup("OLDPWD")));
	if (!ft_is_shlvl(envp))
		ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup("SHLVL=1")));
	if (!ft_is_cm(envp))
		ft_lstadd_back(&envp_list, ft_lstnew(ft_strdup("_=./minishell")));
	return (envp_list);
}
