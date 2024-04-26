/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:56:17 by valarcon          #+#    #+#             */
/*   Updated: 2024/04/26 12:11:58 by valarcon         ###   ########.fr       */
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

int	ret_of_exit(int x, int nb)
{
	while (nb > 255)
		nb = nb - 255;
	if (x == -1)
		nb = 255 - nb;
	return (nb);
}

int	min_atoi(char *str)
{
	long	nb;
	int		i;
	int		x;

	nb = 0;
	i = 0;
	x = 1;
	if (!*str)
		return (0);
	if (str[i] == '-')
	{
		x = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nb += str[i] - '0';
		if (str[i + 1] != '\0')
			nb *= 10;
		else
			return (ret_of_exit(x, nb));
		i++;
	}
	return (256);
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
