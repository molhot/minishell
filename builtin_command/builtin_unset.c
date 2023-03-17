/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:24:47 by user              #+#    #+#             */
/*   Updated: 2023/03/17 11:54:50 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	exportwd_check(char *arg)
{
	if (!('a' <= *arg && *arg <= 'z'))
		if (!('A' <= *arg && *arg <= 'Z'))
			if (*arg != '_')
				return (false);
	arg++;
	while (*arg != '\0' && *arg != '=')
	{
		if (!isascii(*arg))
			return (false);
		arg++;
	}
	return (true);
}

void	ms_unset(char *line, t_command *command)
{
	char	**commands;
	size_t	position;
	bool	not_correctarg;

	(void)line;
	not_correctarg = false;
	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[1] == NULL)
	{
		free_commands(commands);
		return ;
	}
	position = 0;
	while (commands[position] != NULL)
	{
		if (exportwd_check(commands[position]) == false)
		{
			printf("%s\n", "not correct argment!! booboo:X");
			not_correctarg = true;
		}
		else
			map_unset(&g_env, commands[position]);
		position++;
	}
	if (not_correctarg == true)
		g_env->err_status = 1;
	else
		g_env->err_status = 0;
	free_commands(commands);
}
