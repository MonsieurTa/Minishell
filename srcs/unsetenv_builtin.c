/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:59:20 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 20:58:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

void	env_rmkey(char *key, char **new_env, char ***env)
{
	char	buf[MAX_PATH_LEN];
	int		buf_len;
	int		i;
	int		j;

	ft_strcpy(buf, key);
	ft_strcat(buf, "=");
	buf_len = ft_strlen(buf);
	i = -1;
	j = 0;
	while ((*env)[++i] != NULL)
	{
		if (ft_strnequ(buf, (*env)[i], buf_len) == 0)
		{
			new_env[j++] = ft_strdup((*env)[i]);
		}
	}
	ft_splitdel(*env);
	(*env) = new_env;
}

int		unsetenv_builtin(char *key, char ***env)
{
	char	**new_env;
	char	buf[MAX_PATH_LEN];
	int		new_size;

	if (ft_strchr(key, '='))
		return (UNSETENV_USG);
	ft_bzero(buf, MAX_PATH_LEN);
	ft_strcpy(buf, key);
	ft_strcat(buf, "=");
	if (is_set(buf, *env) >= 0)
	{
		new_size = split_counter(*env);
		if ((new_env = (char**)ft_memalloc(sizeof(char*) * new_size)) != NULL)
			env_rmkey(key, new_env, env);
	}
	return (0);
}
