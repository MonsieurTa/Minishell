/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 03:22:49 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:17:27 by wta              ###   ########.fr       */
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

int		env_exec(char **av, char **env)
{
	exec_bin(av, env);
	ft_splitdel(env);
	return (0);
}

int		env_builtin(int ac, char **av, char **env)
{
	char	*needle;
	char	**cpy;
	int		err_id;
	int		idx;

	err_id = 0;
	if ((cpy = envcpy(env)) != NULL)
	{
		idx = 0;
		while (av[++idx] != NULL)
		{
			if ((needle = ft_strchr(av[idx], '=')) != NULL)
			{
				*needle = '\0';
				err_id = setenv_builtin(av[idx], needle + 1, 1, &cpy);
				if (idx == ac - 1)
					print_env(cpy);
			}
			else
				return (env_exec(&av[idx], cpy));
		}
		ft_splitdel(cpy);
	}
	return (err_id);
}
