/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 00:07:40 by wta               #+#    #+#             */
/*   Updated: 2019/01/10 04:54:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h> 
#include <sys/stat.h> 
#include "../libft/includes/libft.h"
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
	else if (ft_strequ(str, "clear") == 1)
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
				if ((pid = fork()) == 0)
					execve(path, bin, env);
				wait(&pid);
				return (1);
			}
		}
		env_path++;
	}
	return (0);
}
