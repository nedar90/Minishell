/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:25:55 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 14:18:39 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	pipes_counter(t_lexer *lexer)
{
	int		num;

	num = 0;
	if (!lexer)
		return (0);
	if (lexer->token == PIPE)
		ft_error(PIPE_ERR, true);
	while (lexer->next)
	{
		if (lexer->token == PIPE)
			num++;
		lexer = lexer->next;
	}
	return (num);
}

int	init_env(t_utils *utils, char **old_env)
{
	int	i;

	i = 0;
	while (old_env[i])
		i++;
	utils->env = malloc(sizeof(char *) * (i + 1));
	if (!utils->env)
		return (-1);
	utils->env[i] = NULL;
	while (old_env[--i])
		utils->env[i] = ft_strdup(old_env[i]);
	return (0);
}

int	init_utils(t_utils *utils)
{
	utils->argv = readline("Minishell: ");
	if (!utils->argv)
	{
		ft_putendl_fd("exit", STDOUT_FILENO, true);
		ft_free(utils->env);
		exit(EXIT_SUCCESS);
	}
	add_history(utils->argv);
	if (check_arg_err(utils->argv))
		return (1);
	lexer(utils);
	utils->pipes = pipes_counter(utils->lexer);
	if (utils->pipes)
		utils->pid = malloc(sizeof(int) * utils->pipes);
	else
		utils->pid = malloc(sizeof(int));
	utils->cmds = NULL;
	return (0);
}
