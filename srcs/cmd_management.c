#include "minishell.h"

void	prompt(void)
{
	ft_printf("%s", "minishell $> ");
}

char **parse_cmd(char *line)
{
	char **cmd;

	cmd = ft_split(line,' ');
	free(line);
	return (cmd);
}

char **get_cmd(void)
{
	char *line;

	prompt();
	while (get_next_line(0, &line)!= 1)
	{
	}
	return(parse_cmd(line));
}

void	launch(char **cmd, int *status)
{
	if (ft_strcmp(cmd[0],"echo") == 0)
		return;
	else if (ft_strcmp(cmd[0],"cd") == 0)
		cd_builtin(cmd);
	else if (ft_strcmp(cmd[0],"pwd") == 0)
		pwd_builtin();
	else if (ft_strcmp(cmd[0],"export") == 0)
		return;
	else if (ft_strcmp(cmd[0],"unset") == 0)
		return;
	else if (ft_strcmp(cmd[0],"env") == 0)
		return;
	else if (ft_strcmp(cmd[0],"exit") == 0)
		*status = exit_builtin();
	else
	{
		execute(cmd);
	}
}

