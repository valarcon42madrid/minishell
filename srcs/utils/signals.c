/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:00:15 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/29 12:02:17 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libminishell.h"

void	signal_child2(int number)
{
	if (number == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		signal(SIGQUIT, SIG_DFL);
	}
	if (number == SIGINT)
		printf("\n");
}

void	signal_child(int number)
{
	if (number == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		signal(SIGQUIT, SIG_DFL);
	}
	if (number == SIGINT)
	{
		printf("\n");
	}
}

void	sig_hd(int n)
{
	if (n == SIGINT)
	{
		g_error_code = 1;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		exit (1);
	}
}

void	signal_handler(int number)
{
	if (number == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_error_code = 1;
		rl_redisplay();
	}
}

void	signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
