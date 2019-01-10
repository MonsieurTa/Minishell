/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 03:22:49 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 06:03:07 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minnishell.h"

static void	env_mod(char *key, char *value, char *keyvalue, char **env)
{
	int	key_size;
	int	idx;

	if (env != NULL)
	{
		key_size = ft_strlen(key);
		idx = -1;
		while (env[++idx] != NULL)
		{
			if (ft_strnequ(key, env[idx], key_size) == 1)
			{
				ft_strdel(&env[idx]);
				env[idx] = keyvalue;
				break ;
			}
		}
	}
	return (env);
}

static int	exec_bin_env_mod(char **bin, char **env)
{
	struct stat	buf;
	pid_t		pid;

	if (lstat(bin[0], &buf) == -1)
		return (1);
	if (S_ISREG(buf.st_mode) == 1 && access(bin[0], X_OK) == 0)
	{
		if ((pid = fork()) == 0)
			execve(bin[0], bin, env);
		wait(&pid);
	}
	else if (S_ISDIR(buf.st_mode) == 1)
		return (2);
	else if (access(bin[0], X_OK) != 0)
		return (3);
	return (0);
}

static void	manage_key_value(int ac, char **av, char **env, t_lst *envcpy)
{
	char	key[MAX_PATH_LEN];
	char	value[MAX_PATH_LEN];
	char	*needle;
	int		idx;

	idx = 0;
	while (av[++idx])
	{
		ft_bzero(key, MAX_PATH_LEN);
		ft_bzero(value, MAX_PATH_LEN);
		ft_strcpy(key, av[idx]);
		if ((needle = ft_strchr(key, '=')) != NULL)
		{
			if (key[0] == '=')
				return (INV_ARG);
			ft_strcpy(value, needle + 1);
			needle[1] = '\0';
			env = env_mod(key, value, av[idx], env);
			if (idx == ac - 1)
				print_env(env);
		}
		exec_bin_env_mod(&av[idx], env);
	}
}

int	env_builtin(int ac, char **av, char **env, t_lst *envcpy)
{
	char	**envcpy;
	int		err_id;

	if ((envcpy = get_env(env)) != NULL)
	{
		if (ac == 1)
			print_env(envcpy);
		else
			err_id = manage_key_value(ac, av, env, envcpy);
		ft_splitdel(envcpy);
	}
	return (err_id);
}
