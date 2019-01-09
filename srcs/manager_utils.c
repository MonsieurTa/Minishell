/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 23:28:59 by wta               #+#    #+#             */
/*   Updated: 2019/01/09 04:22:12 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"

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
