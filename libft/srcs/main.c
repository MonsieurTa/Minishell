/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:42:27 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 20:47:41 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

int	main(int ac, char **ac)
{
	char	*input;

	input = NULL;
	while (1)
	{
		if (get_next_line(0, input) > 0)
			input_manager(input);
	}
	return (0);
}
