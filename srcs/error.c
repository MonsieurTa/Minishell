/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:08:28 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:17:50 by wta              ###   ########.fr       */
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
	if (err_id == SETENV_USG)
		ft_printf("usage: setenv [[Key=Value] | [Key] [Value]]\n", str);
	if (err_id == UNSETENV_USG)
		ft_printf("usage: unsetenv [Key]\n", str);
	if (err_id == FAILFORK)
		ft_printf("-minishell: Fork failed\n", str);
	if (err_id == NOT_DIR)
		ft_printf("-minishell: not a directory: %s\n", str);
}
