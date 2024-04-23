/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:48:31 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/15 17:58:26 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMINISHELL_H
# define LIBMINISHELL_H

# include "../libft/libft.h"
# include "data.h"
# include "prompt.h"
# include "builtins.h"
# include "utils.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>

# define WRITE_END 1
# define READ_END 0

void	*ft_sec_malloc(int size);
void	rl_replace_line(const char *text, int clear_undo);
void	print_welcome(t_shell *shell);
char	*prompt(t_shell *shell);
void	expansive_token_aux_2(t_shell *shell, t_var *var);
void	del_quotes_redirect(t_redirect *redirect);
int		check_split_quote(char *arg);
char	get_quotes_split(char *arg);
int		print_error_cmdo(char **cmd, t_shell *shell);
int		ft_more_error(char *cmd, char **cmdargv, char *cmdcpy, t_shell *shell);
void	ft_cmd_notfound(char *cmd);
char	*ft_protectdot(char *cmd, char	**cmdargv);
int		ft_dir(char *arg);
int		ft_error_filename(char *cmd, char **cmdargv);
int		ft_error_dir(char *cmd, char **cmdargv, char *cmdcpy);
int		ft_error_nosuch(char *cmd, char **cmdargv, char *cmdcpy);
void	print_error_file(char *file);
void	expansive_token(t_shell *shell, char **argv, int np);
void	loop_expa_redirect_input(t_shell *shell, t_redirect *redirect);
void	loop_expa_redirect_output(t_shell *shell, t_redirect *redirect);
int		get_process(t_data *data, char *line);
void	assign_fd_to_process(t_process *lst_process);
void	free_resources(t_process *process);
void	*menu_builtins(void);
int		search_builtins(t_shell *shell);
int		start_process(t_shell *shell);
void	reset_input_mode(void);
void	set_input_mode(void);
void	sort_lst(t_list **lst);
void	free_matrix(char **str);
void	free_redirect(t_redirect *redirect);
void	free_shell_data(t_shell *shell);
char	*ft_justquotes(char *line);
int		ft_esception(char	*str);
int		ft_difquot(char *str);
int		ft_text(char *sh);
void	start_pipe(t_shell *shell, int *num_p, char *line);
void	start_pipe2(t_shell *shell, t_process *process, t_process *pro_pid);
void	get_path(char *cmd, char *envp[], char **f_path, t_list *exp_list);
char	*mini_path(char *envp[], t_list *exp_list);
char	**ft_mypath(char *envp[], t_list *exp_list, char **f_path);
int		fd_input_redirect(t_shell *shell);
int		fd_output_redirect(t_shell *shell);
int		ft_input_heredoc(t_process *process);
int		fd_input_eof(t_redirect *input);
int		ft_fd_valid(int fd);
void	exec_final_child(t_shell *s, t_process *pr,
			int *fd_b, t_process *p_pid);
void	exec_first_child(t_shell *s, t_process *pr,
			t_process *p_pid);
void	exect_b_childs(t_shell *s, t_process *pr,
			int *fd_b, t_process *p_pid);
void	exec_only_one_process(t_shell *shell);
void	ft_forkerror(void);
int		ft_nopath(char *argv);
void	redirect_output_exec(t_shell *shell);
void	redirect_input_exec(t_shell *shell);
int		get_fd_builtins(t_shell *shell);
void	redirect_io(t_shell *shell);
int		ft_protect_void_v(char **argv);
void	ft_closer(t_process	**process_pid, t_process	**safep);
void	ft_closerparent(t_process **process_pid, t_process **safep);
void	ft_closeread(t_process **process_pid);
int		ft_compress_sec_sh(char aux, int *did, char *line, int x);
void	ft_compress_ex_tk_aux(t_var *var);
void	ft_compress_extk_swp(t_var *var, t_shell *shell, int np);
int		ft_compress_swp_aux(char **tmp_matrix, t_var *var);
int		ft_compress_scsh_x(char *line, int x);
void	ft_compresstwo_swp(t_var *var, char *tmp,
			char **tmp_matrix, char **split_matrix);

#endif
