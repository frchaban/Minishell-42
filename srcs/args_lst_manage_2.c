/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_lst_manage_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 18:15:52 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 18:16:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			free_arg_list(t_list *args)
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