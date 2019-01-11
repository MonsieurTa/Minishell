/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 20:20:05 by wta               #+#    #+#             */
/*   Updated: 2019/01/11 21:18:40 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

char	*tilde_expand(char *input, char **env)
{
	char	*str;
	char	*home;
	int		len;

	home = get_hpath(env);
	len = ft_strlen(input);
	str = NULL;
	if (len == 1)
		str = ft_strdup(home);
	else if (input[1] == '/')
		str = ft_strjoin(home, input + 1);
	if (str != NULL)
	{
		ft_strdel(&input);
		input = str;
	}
	return (input);
}

char	*get_env_var(char *input, char **env)
{
	char	buf[MAX_PATH_LEN];
	int		len;
	int		idx;

	ft_strcpy(buf, input);
	ft_strcat(buf, "=");
	len = ft_strlen(buf);
	idx = -1;
	while (env[++idx] != NULL)
	{
		if (ft_strnequ(buf, env[idx], len) == 1)
			return (env[idx] + len);
	}
	return (NULL);
}

char	*dollar_expand(char *input, char **env)
{
	char	*env_var;
	char	*str;

	if ((env_var = get_env_var(&input[1], env)) != NULL)
	{
		if ((str = ft_strdup(env_var)) != NULL)
		{
			ft_strdel(&input);
			return (str);
		}
	}
	return (input);
}

void	manager_expand(char **input, char **env)
{
	char	*home;
	int		len;

	len = ft_strlen(*input);
	home = get_hpath(env);
	if ((*input)[0] == '~' && home != NULL)
		*input = tilde_expand(*input, env);
	else if (len > 1 && (*input)[0] == '$')
		*input = dollar_expand(*input, env);
}

void	input_manager(char *input, char ***env)
{
	char	**cmds;
	int		ret;
	int		idx;

	cmds = NULL;
	if (input != NULL)
	{
		ret = split_by_token(input, &cmds, ";");
		ft_strdel(&input);
		idx = -1;
		while (++idx < ret)
			cmd_manager(cmds[idx], env);
		ft_splitdel(cmds);
	}
}
