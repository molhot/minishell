/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:23:35 by user              #+#    #+#             */
/*   Updated: 2023/03/30 00:37:35 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(void)
{
	char	buf[256];

	getcwd(buf, sizeof(buf));
	if (NULL != getcwd(buf, sizeof(buf)))
		printf("%s\n", buf);
	else
		printf("%s\n", "not correct folda");
	g_env->err_status = 0;
}
