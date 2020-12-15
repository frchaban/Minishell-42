/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_lst_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 17:44:46 by frchaban          #+#    #+#             */
/*   Updated: 2020/12/14 19:13:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



static	t_list	*set_up_arg(char *line)
{
	t_list	*result;

	if (!line)
		return (NULL);
	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	result->content = ft_strdup(line);
	result->next = NULL;
	return (result);
}

static	int		ft_is_redir_symb(char *c)
{
	if (ft_strequ(c, ">") || ft_strequ(c, ">>")
	|| ft_strequ(c, "<"))
		return (1);
	else
		return (0);
}

t_list			*args_to_list_n1(int *first, t_list **args, char **cmd, int *i)
{
	if (!(*args = set_up_arg(cmd[(*i)++])))
		return (NULL);
	*first = 0;
	return (*args);
}

t_list		*args_to_list_n2(t_list **args, char **cmd, int *i)
{
	t_list *new;

	if (!(new = set_up_arg(cmd[(*i)++])))
	{
		free_args_list(*args);
		return (NULL);
	}
	return (new);
}

void		args_to_list(t_list **args, char **cmd)
{
	int		i;
	int		first;
	t_list	*new;

	i = 1;
	first = 1;
	while (cmd[i])
	{
		if (ft_is_redir_symb(cmd[i]))
		{
			i += 1;
			if (!cmd[i++])
				return ;
		}
		if (cmd[i] && !ft_is_redir_symb(cmd[i]))
		{
			if (first)
				new = args_to_list_n1(&first, args, cmd, &i);
			else
			{
				new->next = args_to_list_n2(args, cmd, &i);
				new = new->next;
			}
		}
	}
}
