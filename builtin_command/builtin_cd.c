/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:18:23 by user              #+#    #+#             */
/*   Updated: 2023/04/02 23:17:47 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	show_manual(char **commands)
{
	free_commands(commands);
	ft_putendl_fd("cd with only a relative or absolute path", 2);
	g_env->err_status = 1;
	return ;
}

void	ms_cd(t_command *command)
{
	char	**commands;
	char	buf[256];

	commands = command_to_array(command);
	if (!commands)
		fatal_error("malloc");
	if (commands[1] == NULL || commands[2] != NULL || ft_strchr(commands[1],
			'~'))
		return (show_manual(commands));
	if (chdir(commands[1]) < 0)
	{
		perror("chdir");
		free_commands(commands);
		g_env->err_status = 1;
		return ;
	}
	if (getcwd(buf, sizeof(buf)) == NULL)
		printf("cd: error retrieving current directory: \
		getcwd: cannot access parent directories: No such file or directory\n");
	else
	{
		map_set(&g_env, "OLDPWD", g_env->ms_pwd);
		free(g_env->ms_pwd);
		g_env->ms_pwd = ft_strdup(buf);
		map_set(&g_env, "PWD", g_env->ms_pwd);
	}
	free_commands(commands);
	g_env->err_status = 0;
}
