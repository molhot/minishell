/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:32:50 by satushi           #+#    #+#             */
/*   Updated: 2023/03/17 12:44:30 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = 10;
	while (is_valid_fd(stashfd))
		stashfd++;
	stashfd = xdup2(fd, stashfd);
	xclose(fd);
	return (stashfd);
}

char	*re_makeinwd(char *line)
{
	char	*remake;
	char	*f_line;

	remake = NULL;
	f_line = line;
	while (*line != '\0')
	{
		if (*line == '$')
			expand_doller(&remake, &line, line);
		else
			append_char(&remake, *line++);
	}
	free(f_line);
	return (remake);
}

static	int	heredoc(const char *deli)
{
	char	*line;
	char	*re_line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	while (1)
	{
		line = readline("input > ");
		if (line == NULL)
			break ;
		re_line = re_makeinwd(line);
		if (ft_strcmp(re_line, deli) == 0)
		{
			free(re_line);
			break ;
		}
		ft_putendl_fd(re_line, pfd[1]);
		free(re_line);
	}
	close (pfd[1]);
	return (pfd[0]);
}

void	ready_redirectionfile(t_node *node)
{
	int			fd;
	t_redirect	*redirect;

	while (node != NULL)
	{
		redirect = *(node->command->redirect);
		while (redirect != NULL)
		{
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
			if (fd != -1)
				fd = stashfd(fd);
			redirect->redirectfile = fd;
			redirect = redirect->next;
		}
		node = node->next;
	}
}

int	redirect_reconect(t_command *command)
{
	t_redirect	*redirect;
	int			flag;

	flag = 0;
	if (command->redirect == NULL)
		return (flag);
	redirect = *(command->redirect);
	while (redirect != NULL)
	{
		if (redirect->redirectfile == -1 || redirect->ambigous == true)
			return (1);
		if (redirect->type == IN || redirect->type == HEREDOC)
		{
			redirect->stashed_fd = stashfd(0);
			inout_reconnect(redirect->redirectfile, 0, command);
		}
		if (redirect->type == OUT || redirect->type == APPEND)
		{
			redirect->stashed_fd = stashfd(1);
			inout_reconnect(redirect->redirectfile, 1, command);
		}
		redirect = redirect->next;
	}
	return (flag);
}
