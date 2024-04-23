/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:43:50 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/29 12:13:40 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	print_list(t_list *lst)
{
	if (lst)
	{
		while (lst)
		{
			printf("%s\n", (char *)lst->content);
			lst = lst->next;
		}
	}
}

int	ft_ispwd(char **envp)
{
	while (*envp)
	{
		if ((*envp)[0] && (*envp)[1] && (*envp)[2] && (*envp)[3])
		{
			if ((*envp)[0] == 'P' && (*envp)[1] == 'W' && (*envp)[2] == 'D'
				&& (*envp)[3] == '=')
				return (1);
		}
		envp++;
	}
	return (0);
}

int	ft_isoldpwd(char **envp)
{
	while (*envp)
	{
		if ((*envp)[0] && (*envp)[1] && (*envp)[2] && (*envp)[3]
			&& (*envp)[4] && (*envp)[5] && (*envp)[6])
		{
			if ((*envp)[0] == 'O' && (*envp)[1] == 'L' && (*envp)[2] == 'D'
				&& (*envp)[3] == 'P' && (*envp)[4] == 'W' && (*envp)[5] == 'D'
				&& (*envp)[6] == '=')
				return (1);
		}
		envp++;
	}
	return (0);
}

int	get_var_len(char *str)
{
	int	count;

	count = 0;
	while (str[count] && str[count] != '=')
		count++;
	return (count);
}

void	*ft_sec_malloc(int size)
{
	void	*res;

	if (size > 0)
	{
		res = malloc(size);
		if (res == NULL)
		{
			ft_putstr_fd("Error malloc", 2);
			exit (2);
		}
		return (res);
	}
	else
		return (NULL);
}
