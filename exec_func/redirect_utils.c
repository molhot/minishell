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

char	*re_makeinwd(char *line, const char *deli)
{
	char	*remake;
	char	*f_line;

	remake = NULL;
	f_line = line;
	printf("%s\n", deli);
	while (*line != '\0')
	{
		if (*line == '$' && ft_strchr(deli, '\'') != NULL)
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
		re_line = re_makeinwd(line, deli);
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
