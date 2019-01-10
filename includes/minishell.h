/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:43:20 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 21:40:08 by wta              ###   ########.fr       */
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

void	input_manager(char *input, char ***env);
void	cmd_manager(char *cmd, char ***env);

int		split_by_token(char *input, char ***cmds, char token);
int		split_counter(char **split);
void	ft_splitdel(char **split);
int		is_path(char *str);

void	exec_bin(char **bin, char **env);
int		builtin_id(char *str);
int		echo_builtin(int ac, char **av, char **env);
int		env_builtin(int ac, char **arg, char **env);
int		setenv_builtin(char *key, char *value, int overwrite, char ***env);
int		unsetenv_builtin(char *key, char ***env);

void	signal_handler(int sig);

void	err_handler(int err_id, char *str);

int		is_set(char *key, char **env);
void	print_env(char **env);
char	**get_env(char **env);
char	*get_env_path(char **env);
void	set_stack_path(char path[], char *bin, char *env_path);
int		find_bin(char **env_path, char **bin, char **env);

#endif
