/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:20:05 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 20:44:00 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

static	split_counter(char **split)
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

static int	cmd_counter(char *input, char **cmds)
{
	cmds = ft_strsplit(input, ';');
	return (split_counter(cmds));
}

void	input_manager(char *input)
{
	char	**cmds;
	int		ret;
	int		idx;

	cmd = NULL;
	if (intput != NULL)
	{
		ret = cmd_counter(input, cmds);
		ft_strdel(&input);
		idx = -1;
		while (++idx < ret)
			cmd_manager(cmds[idx]);
	}
}
