/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:06:17 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:08:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

void	exit_builtin(void)
{
	exit(0);
}

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		prompt_msg(g_env);
		signal(SIGINT, sighandler);
	}
}

void	sigfork(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		signal(SIGINT, sigfork);
	}
}
