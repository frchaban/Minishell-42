/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frchaban <frchaban@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 11:40:34 by frchaban          #+#    #+#             */
/*   Updated: 2020/05/25 15:03:33 by frchaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv)
{
	(void)argc;
	/*char *buf;
	char *path;

	path = "srcs";
	chdir(path);
	buf = NULL;
	ft_printf("%s\n", getcwd(buf, 0));
	*/
	echo(argv[1], 0);
	return (0);
}
