/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:19:18 by user              #+#    #+#             */
/*   Updated: 2023/03/17 11:54:18 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_helper(char **commands, size_t position)
{
	write(1, commands[position], ft_strlen(commands[position]));
	if (commands[position + 1] != NULL)
		write(1, " ", ft_strlen(" "));
}

int	ms_echo(char *line, t_command *command)
{
	char	**commands;
	size_t	position;

	(void)line;
	position = 1;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[1] != NULL && ft_strcmp(commands[position], "-n") == 0)
	{
		while (ft_strcmp(commands[position], "-n") == 0)
			position++;
		while (commands[position] != NULL)
		{
			echo_helper(commands, position);
			position++;
		}
	}
	else
	{
		while (commands[position] != NULL)
		{
			echo_helper(commands, position);
			position++;
		}
		write(1, "\n", ft_strlen("\n"));
	}
	free_commands(commands);
	g_env->err_status = 0;
	return (0);
}
