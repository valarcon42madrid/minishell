/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:15:44 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/14 18:03:32 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

int	ft_esception(char	*str)
{
	int		x;
	char	q;

	q = ' ';
	x = 0;
	while (str && str[x])
	{
		if (str[x] == '\'' || str[x] == '\"')
		{
			if (q == str[x])
				q = 'x';
			else if (q == '\'' || q == '\"')
				return (1);
			else
				q = str[x];
		}
		else if (q == 'x' && str[x] != ' ')
			return (0);
		x++;
	}
	return (0);
}

int	ft_difquot(char *str)
{
	int		x;
	char	fq;

	fq = ' ';
	x = 0;
	while (str && str[x] && str[x] != '|')
	{
		if (str[x] == '\'' || str[x] == '\"')
		{
			if (fq == str[x])
				fq = ' ';
			else if (fq == '\'' || fq == '\"')
				return (1);
			else
				fq = str[x];
		}
		else
			return (0);
		x++;
	}
	return (0);
}

t_shell	*ft_init_no_env(void)
{
	char	**envp2;
	char	*aux;
	char	path[1024];
	t_shell	*shell;

	envp2 = (char **)ft_sec_malloc(sizeof(char *) * 5);
	getcwd(path, sizeof(path));
	aux = ft_strjoin("PWD=", path);
	envp2[0] = ft_strdup(aux);
	free (aux);
	envp2[4] = NULL;
	envp2[3] = ft_strdup("OLDPWD");
	envp2[1] = ft_strdup("SHLVL=0");
	envp2[2] = ft_strdup("_=./minishell");
	shell = init_minishell(envp2);
	free(envp2[3]);
	free(envp2[2]);
	free(envp2[1]);
	free(envp2[0]);
	free(envp2);
	return (shell);
}

void	ft_fix_var(char	**av, int ac)
{
	(void)av;
	(void)ac;
	print_header();
	g_error_code = 0;
}

void	ft_preemfree(t_shell	*shell)
{
	if (shell->data->envpget)
		free (shell->data->envpget);
	free (shell->data);
	free (shell);
	write(2, "exit\n", 5);
	exit(0);
}
