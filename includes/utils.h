/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:49:45 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/28 18:54:24 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libminishell.h"

t_list	*fill_envp_list(char **envp);
void	ft_shlvlnext(char **envp, int index, t_list *envp_list);
void	ft_pwd_add(t_list	*envp_list);
int		ft_ispwd(char **envp);
int		ft_isoldpwd(char **envp);
int		ft_is_cm(char **envp);
int		ft_is_shlvl(char **envp);
void	sort_env_list(t_list *lst);
void	print_list(t_list *lst);
char	*search_env(t_list *envp_list, char *name);
void	replace_content_envp(t_data *data, char *content, char *name);
void	replace_content_exp(t_data *data, char *content, char *name);
t_list	*fill_exp_list(char **envp);
int		ft_ispath(char **envp);
char	*fill_with_dquotes(char *envp);
int		get_var_len(char *str);
char	**get_env(t_data *data);
int		min_atoi(char *str);
void	fill_slung_dash(t_data *data);
void	signals(void);
void	signal_handler(int number);
void	signal_child(int number);
void	signal_child2(int number);
void	signals2(void);
void	signal_handler2(int number);
void	sig_hd(int n);
t_shell	*init_minishell(char **envp);
void	ft_fix_var(char **av, int ac);
t_shell	*ft_init_no_env(void);
void	main_loop(t_shell *shell);
void	ft_preemfree(t_shell	*shell);

#endif
