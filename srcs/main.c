/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:42:27 by wta               #+#    #+#             */
/*   Updated: 2019/01/09 04:20:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

static void	init_minishell(int ac, char **av, char **env, t_lst *envcpy)
{
	t_env	*node;
	int		size;
	int		i;

	(void)ac;
	(void)av;
	if ((size = split_counter(env)) > 0)
	{
		i = -1;
		while (++i < size)
		{
			if ((node = newnode(env[i])) != NULL)
				pushback(envcpy, node);
			else
				return ; // TODO rm all lst
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_lst	envcpy;
	char	*input;

	init_lst(&envcpy);
	init_minishell(ac, av, env, &envcpy);
	input = NULL;
	while (1)
	{
		if (get_next_line(0, &input) > 0)
			input_manager(input, &envcpy);
	}
	return (0);
}
