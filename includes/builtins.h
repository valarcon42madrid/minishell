/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:46:22 by valarcon          #+#    #+#             */
/*   Updated: 2022/11/28 18:16:27 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libminishell.h"

void	ft_cd(t_data *data);
char	*ft_perfectdir(t_data	*data);
char	*ft_aux_protect_cwd(t_data	*data);
char	*ft_aux_pwd(t_data	*data);
char	*ft_aux_aux_pwd(t_data	*data);
char	*ft_aux_aux_pc(t_data	*data);
int		check_path(char *path);
int		special_path(t_data *data);
int		cdpath_loop(t_data *data, char **paths);
int		check_for_swung_dash(t_data *data);
void	update_pwd(t_data *data, char *new_pwd);
char	*ft_purepwd(t_data	*data);
void	ft_updateoldpwd(t_data	*data, char *old_pwd);
char	*ft_oldwithpwd(char	*tmp, char	*res, t_data	*data);
char	*ft_errorcwd(char	*old_pwd);
void	ft_echo(t_data *data);
void	ft_env(t_data *data);
int		ft_notfill(char *expenv);
void	ft_exit(t_data *data);
void	ft_export(t_data *data);
int		already_exist(t_list *lst, char *var);
char	*get_name(char *var);
int		check_arg_name(char *arg);
void	not_valid_identifier(char *builtin, char *arg);
void	ft_pwd(t_data *data);
void	ft_unset(t_data *data);

#endif
