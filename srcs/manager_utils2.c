/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:07:40 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:20:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "minishell.h"

int		builtin_id(char *str)
{
	if (ft_strequ(str, "echo") == 1)
		return (1);
	else if (ft_strequ(str, "cd") == 1)
		return (2);
	else if (ft_strequ(str, "setenv") == 1)
		return (3);
	else if (ft_strequ(str, "unsetenv") == 1)
		return (4);
	else if (ft_strequ(str, "env") == 1)
		return (5);
	else if (ft_strequ(str, "exit") == 1)
		return (6);
	return (0);
}

int		find_bin(char **env_path, char **bin, char **env)
{
	char		path[MAX_PATH_LEN];
	struct stat	buf;
	pid_t		pid;

	while (*env_path != NULL)
	{
		set_stack_path(path, bin[0], *env_path);
		if (lstat(path, &buf) != -1)
		{
			if (access(path, X_OK) == 0)
			{
				pid = fork();
				signal(SIGINT, sigfork);
				if (pid == 0)
					execve(path, bin, env);
				wait(&pid);
				return (1);
			}
		}
		env_path++;
	}
	return (0);
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
