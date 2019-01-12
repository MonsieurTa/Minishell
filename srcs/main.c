/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:42:27 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:21:28 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

void	print_env(char **env)
{
	int	idx;

	if (env != NULL)
	{
		idx = -1;
		while (env[++idx] != NULL)
			ft_printf("%s\n", env[idx]);
	}
}

void	init_shell(int ac, char **av, char ***env)
{
	char	**new_env;
	int		idx;
	int		len;

	(void)ac;
	(void)av;
	len = split_counter(*env);
	if ((new_env = (char**)ft_memalloc(sizeof(char*) * (len + 1))) != NULL)
	{
		idx = -1;
		while (++idx < len)
		{
			if ((new_env[idx] = ft_strdup((*env)[idx])) == NULL)
				exit(0);
		}
		*env = new_env;
		return ;
	}
	exit(0);
}

void	prompt_msg(char **env)
{
	char	*logname;
	char	*home;
	char	*pwd;
	int		hlen;

	if ((home = get_hpath(env)) != NULL)
	{
		hlen = ft_strlen(home);
		if ((pwd = get_pwd(env)) != NULL)
		{
			if (ft_strequ(home, pwd) == 1)
				ft_printf("~ ");
			display_cpwd(pwd);
		}
	}
	logname = get_logname(env);
	ft_printf("%s$ ", (logname != NULL) ? logname : "-minishell");
}

int		main(int ac, char **av, char **env)
{
	char	*input;

	g_env = env;
	init_shell(ac, av, &env);
	input = NULL;
	while (1)
	{
		prompt_msg(env);
		signal(SIGINT, sighandler);
		if (get_next_line(0, &input) > 0)
			input_manager(input, &env);
	}
	ft_splitdel(env);
	return (0);
}
