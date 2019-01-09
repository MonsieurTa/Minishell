/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:20:05 by wta               #+#    #+#             */
/*   Updated: 2019/01/09 03:57:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

void		input_manager(char *input, t_lst *env)
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
