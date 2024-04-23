/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valarcon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:49:10 by valarcon          #+#    #+#             */
/*   Updated: 2022/12/19 16:56:07 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

void			print_header(void);
int				get_num_pipe(char *line);
int				pre_parse(char *line);
int				num_arg_process(char *line, t_process *lst_process);
void			change_status_quote(char *line, t_parseo *parse);
char			**get_lines_cmd(char *line, int num_process);
int				error_quote(t_parseo parse);
char			*next_token(char *line);
int				len_token(char *line);
char			**get_tokens_arg(t_process *process, char *line);
char			*ft_isspace(char *str);
void			ft_addlst_back_redirect(t_redirect *redirect,
					t_redirect *new_redirect);
void			ft_addlst_back_process(t_process *process,
					t_process *new_process);
int				get_num_words(char **str);
int				get_num_words_join(char **argv);
char			**ft_matrixjoin(const char **matrix1, const char **matrix2);
char			**final_token(char **argv);
char			*get_redirect(char *line, t_process *lst_process);
int				is_redirect(int c);
char			*set_symbol_redirect(t_redirect *redirect, char *line);
char			*set_file_redirect(t_redirect *redirect, char *line);
void			del_quotes(t_process *process);
void			ft_add_var(t_var	*var);
int				ft_repeatp(char *str);
int				is_quote(char c);
void			len_expansive(t_var *var);
int				get_num_words_matrix(char **str);
char			**matrixjoin(char **str1, char **str2, int insec_point);
void			expansive_swap_case1(t_shell *shell, t_var *var, int np);
void			expansive_swap_case2(t_shell *shell, t_var *var);
void			expansive_swap_case3(t_shell *shell, t_var *var);
int				ft_vcontent(t_var	*var, t_shell	*shell);
char			*ft_secretpath(t_list	*exp_list);
void			ft_add_oldpwd_e(t_shell *shell, t_var *var);
void			ft_add_pwd_e(t_shell *shell, t_var *var);
void			expansive_swap(t_shell *shell, t_var *var, int np);
void			expansive_token_input(t_shell *shell, char **argv);
void			expansive_token_output(t_shell *shell, char **argv);
char			**ft_splitcare(char	*str);
char			*ft_mod_parsequote(t_var var);
char			*ft_noquotes(char *str);
char			*ft_noquotingredir(char *str, int x, int y);
char			*ft_nqredaux(char	*str, int x, int y);
char			*ft_complexnquotred(char *str, int x, int y);
t_parseo		ft_init_arg_of_num_proc(void);
char			*ft_aux_pre_parse(char *line);
void			ft_aux_set_file_red(char **file,
					t_redirect *redirect, int i, char *line);
void			ft_sytax_error(void);
char			*ft_carequotes(char *line);

#endif
