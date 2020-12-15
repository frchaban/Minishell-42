/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 15:03:33 by gdupont           #+#    #+#             */
/*   Updated: 2020/12/15 13:08:36 by user42           ###   ########.fr       */
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

t_env	*ft_last_elem(t_env *env)
{
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	free_all_list(t_env *env)
{
	t_env	*actual;

	actual = env;
	while (env)
	{
		actual = env;
		env = env->next;
		free_elem_list(actual);
	}
}

t_env	*set_up_elem(char *line, int exportable)
{
	int		i;
	t_env	*result;

	i = 0;
	if (!(result = malloc(sizeof(*result))))
		return (NULL);
	while (line[i] != '=' && line[i])
		i++;
	if (!line[i])
		result->content = ft_strdup("");
	else
		result->content = ft_strdup(&line[i + 1]);
	result->key = ft_substr(line, 0, i);
	result->exportable = exportable;
	result->next = NULL;
	return (result);
}

int		envp_to_list(t_env **env, char **envp)
{
	int		i;
	t_env	*new;

	if (!(*env = set_up_elem("?=0", NOT_EXPORT)))
		return (-1);
	i = 0;
	while (envp[i])
	{
		new = *env;
		while (new->next != NULL)
			new = new->next;
		if (!(new->next = set_up_elem(envp[i], EXPORT)))
		{
			free_all_list(*env);
			return (-1);
		}
		i++;
	}
	return (1);
}
