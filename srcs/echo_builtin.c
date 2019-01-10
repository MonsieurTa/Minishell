/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 02:06:35 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 04:51:44 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

int		echo_builtin(int ac, char **av, char **env)
{
	(void)env;
	int	idx;

	if (ac > 1)
	{
		idx = 0;
		while (++idx < ac)
		{
			if (idx < ac - 1)
				ft_printf("%s ", av[idx]);
			else
				ft_printf("%s\n", av[idx]);
		}
	}
	else
		ft_putchar('\n');
	return (0);
}
