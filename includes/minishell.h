/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:43:20 by wta               #+#    #+#             */
/*   Updated: 2019/01/11 21:28:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_PATH_LEN	4096
# define EXIT			-1
# define NON_EXISTENT	1
# define IS_DIRECTORY	2
# define NO_RIGHT		3
# define INV_ARG		4
# define SETENV_USG		5
# define UNSETENV_USG	6
# define FAILFORK		7
# define NOT_DIR		8

char	**g_env;

void	input_manager(char *input, char ***env);
void	cmd_manager(char *cmd, char ***env);

int		split_by_token(char *input, char ***cmds, char *tokens);
int		split_counter(char **split);
void	ft_splitdel(char **split);
int		is_path(char *str);

void	exec_bin(char **bin, char **env);
void	exit_builtin(void);
int		builtin_id(char *str);
int		cd_builtin(int ac, char **av, char ***env);
int		echo_builtin(int ac, char **av, char **env);
int		env_builtin(int ac, char **arg, char **env);
int		setenv_builtin(char *key, char *value, int overwrite, char ***env);
int		unsetenv_builtin(char *key, char ***env);

char	*get_hpath(char **env);
void	manager_expand(char **input, char **env);

void	sighandler(int sig);
void	sigfork(int sig);
void	prompt_msg(char **env);

void	err_handler(int err_id, char *str);

int		is_set(char *key, char **env);
void	print_env(char **env);
char	**get_env(char **env);
char	*get_env_path(char **env);
void	set_stack_path(char path[], char *bin, char *env_path);
int		find_bin(char **env_path, char **bin, char **env);

#endif
