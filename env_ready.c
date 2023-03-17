/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_ready.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochitteiunon? <sakata19991214@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:39:39 by user              #+#    #+#             */
/*   Updated: 2023/03/17 11:43:22 by mochitteiun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*conbinate_keyvalue(t_item *head)
{
	char	*env_remake;
	char	*name;
	char	*value;

	env_remake = NULL;
	name = head->name;
	value = head->value;
	while (*name != '\0')
		append_char(&env_remake, *name++);
	append_char(&env_remake, '=');
	if (value != NULL)
		while (*value != '\0')
			append_char(&env_remake, *value++);
	return (env_remake);
}

char	**ready_nextenviron(void)
{
	t_item	*head;
	char	**n_env;
	size_t	position;

	head = g_env->item_head;
	position = 0;
	while (head != NULL)
	{
		position++;
		head = head->next;
	}
	n_env = (char **)malloc(sizeof(char *) * (position + 1));
	head = g_env->item_head;
	position = 0;
	while (head != NULL)
	{
		n_env[position] = conbinate_keyvalue(head);
		position++;
		head = head->next;
	}
	n_env[position] = NULL;
	return (n_env);
}

char	*get_name(char *name_and_value)
{
	size_t	len;
	size_t	j;
	char	*name;

	len = 0;
	while (name_and_value[len] != '\0')
	{
		if (name_and_value[len] == '=')
			break ;
		len++;
	}
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
		fatal_error("malloc");
	j = 0;
	while (len)
	{
		name[j] = name_and_value[j];
		j++;
		len--;
	}
	name[j] = '\0';
	return (name);
}

void	env_init(t_map **env)
{
	size_t			i;
	char			*name;
	char			*value;
	char			cwd[256];
	extern char		**environ;

	i = 0;
	*env = malloc(sizeof(t_map));
	(*env)->err_status = 0;
	(*env)->item_head = NULL;
	while (environ[i] != NULL)
	{
		name = get_name(environ[i]);
		if (ft_strcmp(name, "PATH") == 0)
			g_env->pwd = ft_strdup(getenv(name));
		value = getenv(name);
		map_set(env, name, value);
		free(name);
		i++;
	}
	getcwd(cwd, sizeof(cwd));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		fatal_error("getcwd");
	map_set(env, "PWD", cwd);
}
