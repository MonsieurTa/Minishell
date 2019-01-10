/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 03:22:49 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 22:51:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

char	**envcpy(char **env)
{
	char	**cpy;
	int		env_len;
	int		idx;

	env_len = split_counter(env);
	if (env != NULL
	&& (cpy = (char**)ft_memalloc(sizeof(char*) * (env_len + 1))))
	{
		idx = -1;
		while (env[++idx] != NULL)
		{
			if ((cpy[idx] = ft_strdup(env[idx])) == NULL)
				exit(0);
		}
		return (cpy);
	}
	return (NULL);
}

int	env_builtin(int ac, char **arg, char **env)
{
	char	*needle;
	char	**cpy;
	int		err_id;
	int		idx;

	err_id = 0;
	if ((cpy = envcpy(env)) != NULL)
	{
		idx = 0;
		while (arg[++idx] != NULL)
		{
			if ((needle = ft_strchr(arg[idx], '=')) != NULL)
			{
				*needle = '\0';
				err_id = setenv_builtin(arg[idx], needle + 1, 1, &cpy);
				if (idx == ac - 1)
					print_env(cpy);
			}
			else
				exec_bin(&arg[idx], cpy);
		}
		ft_splitdel(cpy);
	}
	return (err_id);
}
