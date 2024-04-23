/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:47:39 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 17:32:16 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

int			g_error_code;

typedef int	t_bool;

typedef struct s_parseo
{
	size_t		num_arg;
	size_t		i;
	t_bool		flag;
	t_bool		quotes_d;
	t_bool		quotes_s;

}				t_parseo;

enum	e_boolean
{
	false,
	true
};

typedef struct s_redirect
{
	char				**file;
	char				*symbol;
	int					pos;
	struct s_redirect	*next;
}				t_redirect;

typedef struct s_process
{
	char				**argv;
	t_redirect			*input;
	t_redirect			*output;
	pid_t				pid;
	int					*fd;
	int					fd_out;
	int					status;
	struct s_process	*next;
}				t_process;

typedef struct s_data
{
	t_process		*lst_process;
	t_list			*envp_list;
	t_list			*exp_list;
	t_list			*tmp_var_list;
	char			*swung_dash;
	int				num_p;
	int				num_pi;
	void			*menudir;
	char			**envpget;
	void			*shelldir;
	char			*line;
}				t_data;

typedef struct s_var
{
	int		i;
	int		j;
	int		len_exp;
	char	*content;
	char	*before_exp;
	char	*after_exp;
	char	*join_befor_tmp;
	char	*env;
	char	**token;
	char	**tmp;
	char	*tmp_join;
	char	*aux;
	t_bool	bool;
}				t_var;

typedef struct s_shell
{
	t_data		*data;
	t_bool		status;
}			t_shell;

#endif
