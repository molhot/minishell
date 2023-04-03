/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:23:35 by user              #+#    #+#             */
/*   Updated: 2023/04/03 10:45:23 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	ms_pwd(void)
{
	char		buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
	{
		//printf("%s\n", getenv("PWD"));
		printf("%s\n", map_get(g_env, "PWD"));
	}
	//else //mouikkonohennsuu
	g_env->err_status = 0;
}
