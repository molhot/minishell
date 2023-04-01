/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:19:18 by user              #+#    #+#             */
/*   Updated: 2023/04/01 14:57:07 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		while (commands[position] != NULL && check_option(commands[position]))
			position++;
		if (!commands[position])
			ft_putchar_fd('\0', 1);
		else
		{
			while (commands[position] != NULL)
			{
				ft_putstr_fd(commands[position++], 1);
				if (commands[position] != NULL)
					ft_putstr_fd(" ", 1);
			}
		}
	}
	else
	{
		if (commands[position] == NULL)
			ft_putstr_fd("", 1);
		while (commands[position] != NULL)
		{
			ft_putstr_fd(commands[position++], 1);
			ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
	free_commands(commands);
	g_env->err_status = 0;
	return (0);
}
