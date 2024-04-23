/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:56:09 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/29 11:58:59 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

char	*fill_with_dquotes(char *envp)
{
	char	*tmp;
	int		index;

	tmp = ft_calloc(sizeof(char *), (ft_strlen(envp) + 1));
	if (!tmp)
	{
		ft_putstr_fd("Error malloc", 2);
		exit (2);
	}
	index = 0;
	while (envp[index] != '=')
	{
		tmp[index] = envp[index];
		index++;
	}
	tmp[index] = envp[index];
	index++;
	tmp[index++] = '\"';
	while (envp[index - 1])
	{
		tmp[index] = envp[index - 1];
		index++;
	}
	tmp[index] = '\"';
	return (tmp);
}

int	ft_ispath(char **envp)
{
	while (*envp)
	{
		if ((*envp)[0] && (*envp)[1] && (*envp)[2] && (*envp)[3] && (*envp)[4])
		{
			if ((*envp)[0] == 'P' && (*envp)[1] == 'A'
				&& (*envp)[2] == 'T' && (*envp)[3] == 'H' && (*envp)[4] == '=')
				return (1);
		}
		envp++;
	}
	return (0);
}

t_list	*fill_exp_list(char **envp)
{
	t_list	*lst;

	lst = ft_lstnew(fill_with_dquotes(*envp));
	if (!ft_ispath(envp))
	{
		ft_lstadd_back(&lst, ft_lstnew(fill_with_dquotes
				("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	}
	envp++;
	while (*envp && ft_notfill(*envp))
	{
		ft_lstadd_back(&lst, ft_lstnew(fill_with_dquotes(*envp)));
		envp++;
	}
	return (lst);
}

void	replace_content_exp(t_data *data, char *content, char *name)
{
	t_list	*ptr;
	int		name_len;

	ptr = data->exp_list;
	name_len = get_var_len(name);
	while (data->exp_list)
	{
		if (name_len == get_var_len(data->exp_list->content))
		{
			if (!ft_strncmp(data->exp_list->content, name, name_len))
			{
				free(data->exp_list->content);
				data->exp_list->content = content;
				data->exp_list = ptr;
				return ;
			}
		}
		data->exp_list = data->exp_list->next;
	}
	data->exp_list = ptr;
	ft_lstadd_back(&(data->exp_list), ft_lstnew(content));
	sort_env_list(data->exp_list);
}

void	replace_content_envp(t_data *data, char *content, char *name)
{
	t_list	*ptr;
	int		name_len;

	ptr = data->envp_list;
	name_len = get_var_len(name);
	while (data->envp_list)
	{
		if (name_len == get_var_len(data->envp_list->content))
		{
			if (!ft_strncmp(data->envp_list->content, name, name_len))
			{
				free(data->envp_list->content);
				data->envp_list->content = ft_strdup(content);
				data->envp_list = ptr;
				return ;
			}
		}
		data->envp_list = data->envp_list->next;
	}
	data->envp_list = ptr;
	ft_lstadd_back(&(data->envp_list), ft_lstnew(ft_strdup(content)));
}
