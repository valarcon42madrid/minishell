/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:58:36 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 17:59:33 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	ft_compresstwo_swp(t_var *var, char *tmp,
			char **tmp_matrix, char **split_matrix)
{
	free_matrix(var->token);
	free(tmp);
	var->token = tmp_matrix;
	var->i += (get_num_words_matrix(split_matrix) - 1);
	var->i = 0;
	var->j = 0;
	free_matrix(split_matrix);
}
