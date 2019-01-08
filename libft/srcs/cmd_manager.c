/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:43:35 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 22:39:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

void	cmd_manager(char *cmd)
{
	char	**split;

	if ((split = ft_strsplit(cmd, ' ')) != NULL)
	{
		
	}
}
