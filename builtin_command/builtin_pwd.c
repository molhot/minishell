/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kazuki <kazuki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:23:35 by user              #+#    #+#             */
/*   Updated: 2023/04/02 23:17:56 by kazuki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
		printf("%s\n", g_env->ms_pwd);
	g_env->err_status = 0;
}
