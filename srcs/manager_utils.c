/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 23:28:59 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 00:14:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

void	ft_splitdel(char **split)
{
	int	i;

	if (split)
	{
		i = -1;
		while (split[++i] != NULL)
			ft_strdel(&split[i]);
		free(split);
	}
}

int		split_counter(char **split)
{
	int	count;

	count = 0;
	if (split != NULL)
	{
		while (split[count] != NULL)
			count++;
	}
	return (count);
}

int		split_by_token(char *input, char ***cmds, char token)
{
	*cmds = ft_strsplit(input, token);
	return (split_counter(*cmds));
}

int		is_path(char *str)
{
	int	idx;

	idx = -1;
	while (str[++idx] != '\0')
	{
		if (str[idx] == '/')
			return (1);
	}
	return (0);
}

void	set_stack_path(char path[], char *bin, char *env_path)
{
	int	empty;

	empty = ft_strequ(env_path, "");
	ft_bzero(path, MAX_PATH_LEN);
	ft_strcpy(path, env_path);
	ft_strcat(path, (empty == 1) ? "./" : "/");
	ft_strcat(path, bin);
}
