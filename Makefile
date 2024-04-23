# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valarcon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 17:45:53 by valarcon          #+#    #+#              #
#    Updated: 2022/12/19 15:43:18 by valarcon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = -I$(LIBFT) -I includes/ -lreadline

NAME = minishell

SRCS =	srcs/utils/list_utils					\
		srcs/utils/list_utils2					\
		srcs/utils/list_utils3					\
		srcs/utils/list_utils4					\
		srcs/utils/list_utils5					\
		srcs/utils/main_utils					\
		srcs/utils/main_utils2					\
		srcs/utils/main							\
		srcs/prompt/prompt						\
		srcs/prompt/utils						\
		srcs/prompt/redirect					\
		srcs/builtins/ft_env					\
		srcs/builtins/ft_export/ft_export		\
		srcs/builtins/ft_export/ft_export_utils	\
		srcs/builtins/ft_pwd					\
	 	srcs/builtins/ft_unset					\
		srcs/builtins/ft_echo					\
		srcs/builtins/ft_cd/ft_cd				\
		srcs/builtins/ft_cd/ft_cd_utils			\
		srcs/builtins/ft_cd/ft_cd_utils2		\
		srcs/builtins/ft_exit					\
		srcs/prompt/parseo 						\
		srcs/prompt/pre_parseo					\
		srcs/process/exec						\
		srcs/process/exec_utils					\
		srcs/process/exec_utils2				\
		srcs/process/process					\
		srcs/prompt/parseo_tokens				\
		srcs/prompt/expansive_var				\
		srcs/utils/free							\
		srcs/prompt/parseo_quote				\
		srcs/prompt/utils3						\
		srcs/prompt/compressprompt				\
		srcs/prompt/utils2						\
		srcs/pipex/pipex						\
		srcs/pipex/child_utils					\
		srcs/pipex/child_utils2					\
		srcs/pipex/child_utils3					\
		srcs/pipex/search_path					\
		srcs/pipex/search_redirect				\
		srcs/pipex/child_final					\
		srcs/pipex/child_first					\
		srcs/pipex/childs_between				\
		srcs/pipex/exec_one_process				\
		srcs/pipex/utils						\
		srcs/prompt/expansive_var_utils			\
		srcs/prompt/exp_util					\
		srcs/prompt/expasive_var_case			\
		srcs/utils/compress						\
		srcs/utils/compress2					\
		srcs/utils/signals						\
		srcs/prompt/expansive_redirect

SRCSM = $(addsuffix .c, $(SRCS))
OBJS = $(SRCSM:.c=.o)

LIBFT = libft/libft.a 

CC = gcc -Wall -Wextra -Werror

BLUE = \033[1;34m
GREEN = \033[1;32m
RESET = \033[0m

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) ./includes/libminishell.h ./includes/prompt.h ./includes/builtins.h ./includes/utils.h ./includes/data.h
	@make -sC ./libft
	@echo "$(BLUE)      ------- MINISHELL IS BEING CREATED ---------    $(RESET)"
	@$(CC) $(INCLUDES) ${OBJS} $(LIBFT) -o ${NAME} -lreadline -L/Users/${USER}/.brew/opt/readline/lib -I/Users/${USER}/.brew/opt/readline/include
	@echo "Is called: 'minishell'"

clean:
	@$(RM) $(OBJS)
	@echo "$(GREEN)              ---CLEANED---            $(RESET)"
	@make -sC ./libft/ fclean

fclean: clean
	@$(RM) ${NAME}

re : fclean all

.PHONY: all clean fclean re addsuffix
