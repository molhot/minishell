/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 21:06:33 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/26 21:06:33 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	obtain_fd(t_redirect *redirect)
{
	int	fd;

	if (redirect->type == IN)
		fd = open(redirect->file_path, O_RDONLY);
	if (redirect->type == HEREDOC)
		fd = heredoc(redirect->file_path);
	if (redirect->type == OUT)
		fd = open(redirect->file_path, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirect->type == APPEND)
		fd = open(redirect->file_path, \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}
