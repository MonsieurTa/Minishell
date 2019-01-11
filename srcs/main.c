/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:42:27 by wta               #+#    #+#             */
/*   Updated: 2019/01/11 22:06:47 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

void	print_env(char **env)
{
	int	idx;

	if (env !=  NULL)
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

char	*get_pwd(char **env)
{
	int	idx;

	if (env != NULL)
	{
		idx = -1;
		while (env[++idx] != NULL)
		{
			if (ft_strnequ("PWD=", env[idx], 4) == 1)
				return (env[idx] + 4);
		}
	}
	return (NULL);
}

void	display_cpwd(char *pwd)
{
	int	len;

	len = ft_strlen(pwd);
	while (len >= 0 && pwd[len] != '/')
		len--;
	(len != 0) ? ft_printf("%s ", pwd + len + 1) : ft_printf("%s ", pwd);
}

char	*get_logname(char **env)
{
	int	idx;

	if (env != NULL)
	{
		idx = -1;
		while (env[++idx] != NULL)
		{
			if (ft_strnequ("LOGNAME=", env[idx], 8) == 1)
				return (env[idx] + 8);
		}
	}
	return (NULL);
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
	ft_printf("%s$ ", (logname != NULL) ? logname : "Minishell");
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	signal(SIGINT, sighandler);
	init_shell(ac, av, &env);
	g_env = env;
	input = NULL;
	while (1)
	{
		prompt_msg(env);
		if (get_next_line(0, &input) > 0)
			input_manager(input, &env);
	}
	ft_splitdel(env);
	return (0);
}
