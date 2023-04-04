/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:21:24 by user              #+#    #+#             */
/*   Updated: 2023/04/04 19:34:09 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_exit(char *line, t_command *command)
{
	char	**commands;

	(void)line;
	commands = command_to_array(command);
	if (commands[2] != NULL)
	{
		printf("too many argments\n");
		g_env->err_status = 1;
		return ;
	}
	if (!commands)
		fatal_error("malloc");
	if (commands[1] == NULL)
	{
		printf("exit\n");
		exit(g_env->err_status);
	}
	if (!ms_atoi(commands[1]) || (ms_atoi(commands[1]) == -1 \
		&& ft_strlen(commands[1]) > 2))
	{
		printf("exit\n");
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	printf("exit\n");
	exit(ms_atoi(commands[1]));
}
