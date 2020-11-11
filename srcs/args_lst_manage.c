/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_lst_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 17:44:46 by frchaban          #+#    #+#             */
/*   Updated: 2020/10/01 18:48:54 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void		free_arg_list(t_list *args)
{
	free(args->content);
	args->content = NULL;
	free(args);
}

void			free_args_list(t_list *args)
{
	t_list	*actual;
	t_list	*temp;

	actual = args;
	while (actual)
	{
		temp = actual;
		actual = actual->next;
		free_arg_list(temp);
	}
	args = NULL;
}

static t_list	*set_up_arg(char *line)
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

static int		ft_is_redir_symb(char *c)
{
	if (ft_strequ(c, ">") || ft_strequ(c, ">>")
	|| ft_strequ(c, "<"))
		return (1);
	else
		return (0);
}

int				args_to_list(t_list **args, char **cmd)
{
	int		i;
	t_list	*new;

	i = 1;
	if (ft_is_redir_symb(cmd[i]))
		i += 2;
	if (!(*args = set_up_arg(cmd[i])))
		return (-1);
	while (cmd[++i])
	{
		if (ft_is_redir_symb(cmd[i]))
			i += 1;
		else
		{
			new = *args;
			while (new->next != NULL)
				new = new->next;
			if (!(new->next = set_up_arg(cmd[i])))
			{
				free_args_list(*args);
				return (-1);
			}
		}
	}
	return (1);
}
