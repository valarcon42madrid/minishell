/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:56:17 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/29 12:13:17 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	fill_slung_dash(t_data *data)
{
	char	*tmp;

	tmp = search_env(data->envp_list, "USER");
	data->swung_dash = ft_strjoin("/Users/", tmp + 5);
	free(tmp);
}

int	min_atoi(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	if (!*str)
		return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		nb += str[i] - '0';
		if (str[i + 1] != '\0')
			nb *= 10;
		else
			return (nb);
		i++;
	}
	return (-1);
}

static int	get_list_length(t_list *lst)
{
	int	length;

	length = 0;
	while (lst)
	{
		lst = lst->next;
		length++;
	}
	return (length);
}

char	**get_env(t_data *data)
{
	char	**envp;
	t_list	*lst;
	int		index;

	if (data->envpget)
		free (data->envpget);
	envp = (char **)ft_sec_malloc(sizeof(char *)
			* (get_list_length(data->envp_list) + 1));
	if (!envp)
		return (0);
	lst = data->envp_list;
	index = 0;
	while (lst)
	{
		envp[index] = (lst->content);
		lst = lst->next;
		index++;
	}
	envp[index] = 0;
	data->envpget = envp;
	return (envp);
}
