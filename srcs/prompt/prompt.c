/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:14:50 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 12:28:18 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	print_header(void)
{
	ft_putstr_fd("\n", STDIN_FILENO);
	ft_putstr_fd("The default interactive shell is now zsh.\n", STDIN_FILENO);
	ft_putstr_fd("To update your account to use zsh, please run", STDIN_FILENO);
	ft_putstr_fd(" `chsh -s /bin/zsh`.\n", STDIN_FILENO);
	ft_putstr_fd("For more details, please visit ", STDIN_FILENO);
	ft_putstr_fd("https://support.apple.com/kb/HT208050.\n", STDIN_FILENO);
}

char	*prompt(t_shell *shell)
{
	char	*line;
	char	*prompt;
	char	*path;
	char	**split_path;
	int		fd;

	(void)shell;
	fd = dup(1);
	line = NULL;
	path = getcwd(NULL, 0);
	split_path = ft_split(path, '/');
	free(path);
	if (!*split_path)
	{
		split_path = (char **)ft_sec_malloc(sizeof(char *) * 2);
		split_path[0] = ft_strdup("/");
		split_path[1] = NULL;
	}
	prompt = ft_strdup("42_MiniShell: ");
	dup2(STDIN_FILENO, 1);
	line = readline(prompt);
	dup2(fd, 1);
	free(prompt);
	free_matrix(split_path);
	return (line);
}
