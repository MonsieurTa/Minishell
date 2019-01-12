/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:40:44 by wta               #+#    #+#             */
/*   Updated: 2019/01/12 01:21:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*del_tab(char **tab, int len)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (++i < len)
			ft_strdel(&tab[i]);
		free(tab);
		tab = NULL;
	}
	return (NULL);
}

static void	splitbuf(char *str, char *tokens)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i] != '\0')
	{
		j = -1;
		while (tokens[++j] != '\0')
		{
			if (str[i] == tokens[j])
				str[i] = '\0';
		}
	}
}

static int	cnt_wd(char *str, int len)
{
	int	count;
	int	wd;
	int	i;

	count = 0;
	i = -1;
	wd = 0;
	while (++i < len)
	{
		if (wd == 0 && str[i] != '\0')
		{
			count++;
			wd = 1;
		}
		else if (str[i] == '\0')
			wd = 0;
	}
	return (count);
}

static char	*dup_n_wd(char *buf, int len, int n)
{
	int	nwd;
	int	wd;
	int	i;

	i = -1;
	wd = 0;
	nwd = 0;
	while (++i < len)
	{
		if (wd == 0 && buf[i] != '\0')
		{
			if (nwd == n)
				return (ft_strdup(&buf[i]));
			nwd++;
			wd = 1;
		}
		else if (buf[i] == '\0')
			wd = 0;
	}
	return (NULL);
}

char		**ft_strsplit(char const *s, char *tokens)
{
	char	**split;
	char	buf[4096];
	int		len;
	int		wdct;
	int		idx;

	split = NULL;
	if (s != NULL)
	{
		ft_bzero(buf, 4096);
		ft_strcpy(buf, s);
		splitbuf(buf, tokens);
		len = ft_strlen(s);
		wdct = cnt_wd(buf, len);
		if ((split = (char**)ft_memalloc((sizeof(char*) * (wdct + 1)))) != NULL)
		{
			idx = -1;
			while (++idx < wdct)
			{
				if ((split[idx] = dup_n_wd(buf, len, idx)) == NULL)
					return (del_tab(split, len));
			}
		}
	}
	return (split);
}
