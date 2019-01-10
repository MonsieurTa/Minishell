/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 04:29:07 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 06:10:06 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_printf.h"
#include "../libft/includes/libft.h"
#include "minishell.h"

int	is_set(char *key, char **env)
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
				return (idx);
		}
	}
	return (-1);
}

char	**env_mod(char *buf, char **env)
{
	char	**new_env;
	int		env_size;
	int		idx;

	env_size = split_counter(env);
	if ((new_env = (char**)ft_memalloc(sizeof(char*) * (env_size + 1))) != NULL)
	{
		idx = -1;
		while (++idx < env_size)
			new_env[idx] = ft_strdup(env[idx]);
		new_env[idx] = ft_strdup(buf);
		ft_splitdel(env);
	}
	return (new_env);
}

int	setenv_builtin(char *key, char *value, char **env)
{
	char	buf[MAX_PATH_LEN];
	int		key_size;
	int		idx;

	if (env != NULL)
	{
		ft_bzero(buf, MAX_PATH_LEN);
		key_size = ft_strlen(key);
		ft_strcpy(buf, key);
		buf[key_size] = '=';
		ft_strcat(buf, value);
		if ((idx = is_set(key, env)) >= 0)
		{
			if ((env[idx] = ft_strdup(buf)) == NULL)
				return (EXIT);
		}
		else if ((env = env_mod(buf, env)) == NULL)
			return (EXIT);
		print_env(env);
	}
	return (0);
}
