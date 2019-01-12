/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 04:29:07 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:16:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_printf.h"
#include "../libft/includes/libft.h"
#include "minishell.h"

int		is_set(char *key, char **env)
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

char	**env_addkey(char *buf, char **env)
{
	char	**new_env;
	int		env_size;
	int		idx;

	env_size = split_counter(env);
	if ((new_env = (char**)ft_memalloc(sizeof(char*) * (env_size + 2))) != NULL)
	{
		idx = -1;
		while (++idx < env_size)
			new_env[idx] = ft_strdup(env[idx]);
		new_env[idx] = ft_strdup(buf);
		ft_splitdel(env);
	}
	return (new_env);
}

char	*ft_strtcpy(char *dst, char *src, char token)
{
	int	idx;

	idx = -1;
	while (src[++idx] != '\0')
	{
		dst[idx] = src[idx];
		if (src[idx] == token)
			break ;
	}
	return (dst);
}

int		setenv_builtin(char *key, char *value, int overwrite, char ***env)
{
	char	buf[MAX_PATH_LEN];
	char	*needle;
	int		idx;

	ft_bzero(buf, MAX_PATH_LEN);
	ft_strtcpy(buf, key, '=');
	if ((needle = ft_strchr(key, '=')) == NULL && value != NULL)
		ft_strcat(buf, "=");
	else if ((needle == NULL && value == NULL) || buf[0] == '=')
		return (5);
	if ((idx = is_set(buf, *env)) >= 0 && overwrite != 0)
	{
		(ft_strchr(key, '=') != NULL) ? ft_strcat(buf, needle + 1)
		: ft_strcat(buf, value);
		needle = (*env)[idx];
		if (((*env)[idx] = ft_strdup(buf)) == NULL)
			return (EXIT);
		ft_strdel(&needle);
	}
	else if ((*env = env_addkey((needle != NULL) ? key
		: ft_strcat(buf, value), *env)) == NULL)
		return (EXIT);
	return (0);
}
