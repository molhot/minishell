/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:27:43 by satushi           #+#    #+#             */
/*   Updated: 2023/04/11 21:41:49 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map		*g_env;

static void	redirectfile_check(t_redirect *redirect)
{
	int	fd;

	if (redirect->file_path == NULL || redirect->ambigous == true)
		printf("minishell: %s: ambiguous redirect\n", \
		redirect->file_path);
	else
	{
		if (redirect->type == IN)
			fd = open(redirect->file_path, O_RDONLY);
		if (redirect->type == OUT)
			fd = open(redirect->file_path, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redirect->type == APPEND)
			fd = open(redirect->file_path, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd != -1)
			close (fd);
		write(2, "minishell: ", 12);
		perror(redirect->file_path);
	}
	g_env->err_status = 1;
}

static	void	only_redirectch(t_node *node)
{
	t_redirect	*redirect;
	
	redirect = *(node->command->redirect);
	while (redirect != NULL)
	{
		if (redirect->redirectfile == -1 || redirect->ambigous == true)
			redirectfile_check(redirect);
		redirect = redirect->next;
	}
	g_env->err_status = 1;
}

static void	exec_switching(t_node *node)
{
	if (node->command->args == NULL && node->command->redirect != NULL)
	{
		ready_redirection_file(node);
		while (node != NULL)
		{
			only_redirectch(node);
			node = node->next;
		}
	}
	else if (node->next == NULL && is_builtin(node->command->args->word))
		builtin_exec(node);
	else if (node->command->args->word != NULL)
		exec(node);
	else
	{
		printf("minishell: :command not found\n");
		g_env->err_status = 127;
	}
}

static void	readline_execpart(char *line)
{
	t_token	*tok;
	t_node	*node;

	signal(SIGINT, SIG_IGN);
	tok = tokenizer(line);
	if (tokcheck(tok) == false || tokwdcheck(tok) == false)
	{
		free_token(tok);
		return ;
	}
	node = parse(tok);
	expand(node);
	exec_switching(node);
	if (tok != NULL)
		free_token(tok);
	if (node != NULL)
		free_node(node);
}

static void	exit_f(void)
{
	printf("exit\n");
	exit(g_env->err_status);
}

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	env_init();
	while (1)
	{
		g_env->readline_interrupted = false;
		g_env->heredoc = false;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell$ ");
		if (line == NULL)
			exit_f();
		if (*line != 0)
		{
			if (*line)
				add_history(line);
			readline_execpart(line);
		}
		free(line);
	}
}
