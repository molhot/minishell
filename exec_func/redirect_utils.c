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

static char	*re_makeinwd(char *line, bool exok, const char *deli)
{
	char	*remake;
	char	*f_line;

	remake = NULL;
	f_line = line;
	while (*line != '\0')
	{
		if (*line == '$' && exok == true && ft_strcmp(line, deli) != 0)
			expand_doller(&remake, &line, line);
		else
			append_char(&remake, *line++);
	}
	free(f_line);
	return (remake);
}

static int	check_state(void)
{
	if (g_env->heredoc == true)
	{
		g_env->heredoc = false;
		g_env->readline_interrupted = true;
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}

static int	heredoc_loop(const char *deli, bool ex_od, int pfd)
{
	char	*line;
	char	*re_line;

	while (1)
	{
		if (g_env->readline_interrupted)
			break ;
		line = readline("input > ");
		if (line == NULL)
			break ;
		if (g_env->readline_interrupted)
		{
			free(line);
			break ;
		}
		re_line = re_makeinwd(line, ex_od, deli);
		if (ft_strcmp(re_line, deli) == 0)
		{
			free(re_line);
			break ;
		}
		ft_putendl_fd(re_line, pfd);
		free(re_line);
	}
	return (0);
}

static	int	heredoc(const char *deli, bool ex_ok)
{
	int		pfd[2];
	int		res;

	if (pipe(pfd) < 0)
		fatal_error("pipe");
	rl_event_hook = check_state;
	g_env->heredoc = false;
	signal(SIGINT, signal_handler);
	res = heredoc_loop(deli, ex_ok, pfd[1]);
	close (pfd[1]);
	if (res == -1)
	{
		close(pfd[0]);
		signal(SIGINT, SIG_IGN);
		rl_event_hook = NULL;
		return (-1);
	}
	rl_event_hook = NULL;
	if (g_env->readline_interrupted)
	{
		close(pfd[0]);
		signal(SIGINT, SIG_IGN);
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	return (pfd[0]);
}

int	obtain_fd(t_redirect *redirect)
{
	int	fd;

	if (redirect->file_path == NULL)
		return (-1);
	if (redirect->type == IN)
		fd = open(redirect->file_path, O_RDONLY);
	if (redirect->type == HEREDOC)
		fd = heredoc(redirect->file_path, redirect->expand_ok);
	if (redirect->type == OUT)
		fd = open(redirect->file_path, \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirect->type == APPEND)
		fd = open(redirect->file_path, \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}
