/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:20:05 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 19:45:54 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

#include <stdio.h>

void		input_manager(char *input, char ***env)
{
	char	**cmds;
	int		ret;
	int		idx;

	cmds = NULL;
	if (input != NULL)
	{
		ret = split_by_token(input, &cmds, ';');
		ft_strdel(&input);
		idx = -1;
		while (++idx < ret)
			cmd_manager(cmds[idx], env);
		ft_splitdel(cmds);
	}
}
