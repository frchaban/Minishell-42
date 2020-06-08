/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 15:03:33 by gdupont           #+#    #+#             */
/*   Updated: 2020/06/08 16:10:41 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_elem_list(t_env *env)
{
	free(env->key);
	env->key = NULL;
	free(env->content);
	env->content = NULL;
	free(env);
}

void	free_all_list(t_env *env)
{
	t_env	*actual;
	t_env	*temp;

	actual = env;
	while (actual)
	{
		temp = actual;
		actual = actual->next;
		free_elem_list(temp);
	}
	env = NULL;
}

t_env	*set_up_elem(char *line)
{
	int		i;
	t_env	*result;

	i = 0;
	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	while (line[i] != '=' && line[i])
		i++;
	result->key = ft_substr(line, 0, i);
	result->content = ft_strdup(&line[i + 1]);
	result->next = NULL;
	return (result);
}

int		envp_to_list(t_env **env, char **envp)
{
	int		i;
	t_env	*new;

	if (!(*env = set_up_elem(envp[0])))
		return (-1);
	i = 1;
	while (envp[i])
	{
		new = *env;
		while (new->next != NULL)
			new = new->next;
		if (!(new->next = set_up_elem(envp[i])))
		{
			free_all_list(*env);
			return (-1);
		}
		i++;
	}
	return (1);
}