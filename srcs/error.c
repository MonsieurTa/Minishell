/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:08:28 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 05:18:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/ft_printf.h"
#include "minishell.h"

void	err_handler(int err_id, char *str)
{
	if (err_id == EXIT)
		exit(0);
	if (err_id == NON_EXISTENT)
		ft_printf("-minishell: %s: No such file or directory\n", str);
	if (err_id == IS_DIRECTORY)
		ft_printf("-minishell: %s: is a directory\n", str);
	if (err_id == NO_RIGHT)
		ft_printf("-minishell: %s: Permission denied\n", str);
	if (err_id == INV_ARG)
		ft_printf("-minishell: %s: Invalid argument\n", str);
	if (err_id == SETENV_USAGE)
		ft_printf("-minishell: setenv [Key] [Value]\n", str);
}
