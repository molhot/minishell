/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specialparam.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 04:55:20 by mochitteiun       #+#    #+#             */
/*   Updated: 2023/03/12 04:55:20 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	switch_doller(char **new_word, char **args)
{
	if (**args == '$' && *(*args + 1) == '\0')
	{
		append_char(&(*new_word), **args);
		(*args)++;
	}
	else if (**args == '$' && (*(*args + 1) == '\'' || *(*args + 1) == '\"'))
		(*args)++;
	else if (**args == '$' && *(*args + 1) == '?')
		expand_dolleeques(&(*new_word), &(*args), *args);
	else if (**args == '$')
		expand_doller(&(*new_word), &(*args), *args);
}

static void	quote_append_indoller(char type, char **new, char **args)
{
	append_char(&(*new), **args);
	(*args)++;
	if (**args == '\0')
		return ;
	while (**args != type)
	{
		if (**args == '\\' && type == '\"')
		{
			append_char(&(*new), **args);
			(*args)++;
		}
		append_char(&(*new), **args);
		(*args)++;
	}
	append_char(&(*new), **args);
	(*args)++;
}

static char	*expand_args_doller(char *args)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\\')
		{
			append_char(&new_word, *args++);
			append_char(&new_word, *args++);
		}
		else if (*args == '\'' || *args == '\"')
			quote_append_indoller(*args, &new_word, &args);
		else if (*args == '$')
			switch_doller(&new_word, &args);
		else
			append_char(&new_word, *args++);
	}
	return (new_word);
}

void	expand_specialparam(t_token *token)
{
	char	*tmp;

	while (token != NULL)
	{
		tmp = ft_strdup(token->word);
		free(token->word);
		token->word = expand_args_doller(tmp);
		free(tmp);
		token = token->next;
	}
}
