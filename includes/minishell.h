/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 19:43:20 by wta               #+#    #+#             */
/*   Updated: 2019/01/09 04:51:28 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_PATH_LEN 4096

typedef struct	s_env
{
	struct s_env	*next;
	char			*str;
}				t_env;

typedef struct	s_lst
{
	t_env	*head;
	t_env	*tail;
	int		len;
}				t_lst;

t_env	*newnode(char *str);
void	init_lst(t_lst *lst);
void	pushback(t_lst *lst, t_env *node);
void	rm_node(t_lst *lst, char *str);
void	rm_list(t_lst *lst);

void	input_manager(char *input, t_lst *env);
void	cmd_manager(char *cmd, t_lst *env);

void	ft_splitdel(char **split);
int		split_by_token(char *input, char ***cmds, char token);
int		split_counter(char **split);
void	ft_splitdel(char **split);

#endif
