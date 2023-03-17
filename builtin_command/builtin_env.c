/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:20:06 by user              #+#    #+#             */
/*   Updated: 2023/03/17 11:54:26 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_env(void)
{
	t_item	*itr;

	itr = g_env->item_head;
	while (itr != NULL)
	{
		if (itr->value != NULL)
			printf("%s=%s\n", itr->name, itr->value);
		itr = itr->next;
	}
	g_env->err_status = 0;
}
