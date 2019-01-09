/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 02:34:26 by wta               #+#    #+#             */
/*   Updated: 2019/01/09 03:09:11 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "minishell.h"

void	init_lst(t_lst *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

t_env	*newnode(char *str)
{
	t_env	*node;

	if ((node = (t_env*)ft_memalloc(sizeof(t_env))) != NULL)
	{
		node->next = NULL;
		if ((node->str = ft_strdup(str)) == NULL)
		{
			free(node);
			node = NULL;
		}
	}
	return (node);
}

void	pushback(t_lst *lst, t_env *node)
{
	if (lst->len == 0)
	{
		lst->head = node;
		lst->tail = NULL;
	}
	else if (lst->len == 1)
	{
		lst->tail = node;
		lst->head->next = lst->tail;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
	lst->len += 1;
}

void	rm_node(t_lst *lst, char *str)
{
	t_env	*node;
	t_env	*prev;
	int		i;

	if (lst->len > 0 && (node = lst->head) != NULL)
	{
		prev = NULL;
		i = -1;
		while (node != NULL && ++i < lst->len)
		{
			prev = (i > 0) ? node : NULL;
			if (ft_strequ(str, node->str) == 1)
			{
				if (prev != NULL)
					prev->next = node->next;
				ft_strdel(&node->str);
				free(node);
				node = (prev != NULL) ? prev->next : NULL;
				lst->len -= 1;
			}
			else
				node = node->next;
		}
	}
}

void	rm_list(t_lst *lst)
{
	t_env	*node;
	t_env	*tmp;

	if (lst->len > 0 && (node = lst->head) != NULL)
	{
		while (node != NULL && lst->len-- > 0)
		{
			tmp = node;
			node = node->next;
			ft_strdel(&tmp->str);
			free(tmp);
		}
	}
}
