/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manage_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdupont <gdupont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 16:59:57 by frchaban          #+#    #+#             */
/*   Updated: 2020/06/08 19:14:16 by gdupont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    lst_size(t_env  *env)
{
  int i;
  i = 0;
  while (env != NULL)
  {
    i++;
    env = env->next;
  }
  return (i);
}

char  **list_to_envp(t_env *env)
{
  char  **final;
  int    i;
  int    len;
  int    size;
  size = lst_size(env);
  if (!(final = malloc(sizeof(*final) * (size + 1))))
    return (NULL);
  i = 0;
  while (env)
  {
    len = ft_strlen(env->key) + ft_strlen(env->content) + 1;
    if (!(final[i] = malloc(sizeof(**final) * (len + 1))))
      	return(NULL);
    final[i][0] = '\0';
    ft_strcat(final[i], env->key);
    ft_strcat(final[i], "=");
    ft_strcat(final[i], env->content);
    i++;
    env = env->next;
  }
  final[i] = NULL;
  return (final);
}

t_env	*ft_last_elem(t_env *env)
{
	while(env->next != NULL)
		env = env->next;
	return (env);
}
