/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:11:24 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/08 18:18:51 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	redirect_io(t_shell *shell)
{
	redirect_input_exec(shell);
	redirect_output_exec(shell);
}

int	get_fd_builtins(t_shell *shell)
{
	int	fd_out;

	fd_out = fd_output_redirect(shell);
	if (fd_out < 0 && fd_out != -2)
		fd_out = STDOUT_FILENO;
	return (fd_out);
}

int	ft_protect_void_v(char **argv)
{
	int		x;
	int		i;

	x = 0;
	i = 0;
	if (!argv)
		return (0);
	while (argv[x] && !ft_strcmp(argv[x], ""))
	{
		i = x;
		x++;
		while (argv[x] && !ft_strcmp(argv[x], ""))
			x++;
		if (argv[x] && argv[x] != NULL)
		{
			free (argv[i]);
			argv[i] = argv[x];
			argv[x] = NULL;
			x = i + 1;
		}
	}
	return (1);
}

char	*ft_mod_parsequote(t_var	var)
{
	if ((!strcmp(var.aux, "\"\"") || !strcmp(var.aux, "\'\'")))
	{
		free(var.tmp_join);
		var.tmp_join = ft_strdup("\" \"");
	}
	return (var.tmp_join);
}
