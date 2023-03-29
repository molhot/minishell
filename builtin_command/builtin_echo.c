/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:19:18 by user              #+#    #+#             */
/*   Updated: 2023/03/30 00:26:33 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_helper(char **commands, size_t *position)
{
	write(1, commands[*position], ft_strlen(commands[*position]));
	if (commands[*position + 1] != NULL)
		write(1, " ", ft_strlen(" "));
	*position = *position + 1;
}

bool	check_option(char *option)
{
	size_t	i;

	if (option[0] == '-')
	{
		i = 1;
		while (option[i] == 'n')
			i++;
		if (option[i] != '\0')
			return (false);
		else
			return (true);
	}
	return (false);
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
	if (commands[1] != NULL && check_option(commands[position]))
	{
		position++;
		while (commands[position] != NULL)
			echo_helper(commands, &position);
	}
	else
	{
		while (commands[position] != NULL)
			echo_helper(commands, &position);
		write(1, "\n", ft_strlen("\n"));
	}
	free_commands(commands);
	g_env->err_status = 0;
	return (0);
}
