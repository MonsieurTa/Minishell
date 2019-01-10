/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:04:39 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 04:45:40 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

char	*get_env_path(char **env)
{
	int	idx;

	if (env != NULL)
	{
		idx = -1;
		while (env[++idx] != NULL)
		{
			if (ft_strnequ(env[idx], "PATH=", 5) == 1)
				return (env[idx]);
		}
	}
	return (NULL);
}
