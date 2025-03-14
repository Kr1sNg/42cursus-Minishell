/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 14:15:15 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

t_env	ft_initialization(int argc, char **argv, char **env)
{
	t_env infos;
	
	(void)argc;
	(void)argv;
	infos.status = 0;
	infos.fd_in = STDIN_FILENO;
	infos.fd_out = STDOUT_FILENO;
	cmd_create_env(&infos, env);
	cmd_create_export(&infos);
	infos.ast = NULL;
	infos.input = NULL;
	infos.tokens = NULL;
	return (infos);
}

int	main(int argc, char *argv[], char *env[])
{
	t_env	infos;

	if (argc > 1)
		return (ft_error_target(argv[1]), exit(127), 0);
	infos = ft_initialization(argc, argv, env);
	while (1)
	{
		setup_signal_handlers();
		infos.input = readline("minishell:~ $ ");
		if ((!infos.input) || !ft_strcmp(ft_cvt_cmd_on(infos.input), "exit")) // quand on faire "exit" on dois nettoyer tout avant!
		{
			if (infos.input && !ft_strcmp(ft_cvt_cmd_on(infos.input), "exit"))
				infos.status = 0;
			break ;
		}
		add_history(infos.input); // to save history and move up - down cmd
		infos.tokens = ft_tokenize(infos.input);
		infos.ast = ft_parse(infos.tokens);
		infos.status = ft_status_value(&infos);
		// infos.status = ft_execute(infos.ast, &infos);
		ft_free_cmd(&infos);
	}
	ft_finish(&infos);
	return (infos.status);
}

/* free ast, tokens, input after each command line */
void ft_free_cmd(t_env *infos)
{
	infos->fd_in = STDIN_FILENO;
	infos->fd_out = STDOUT_FILENO;
	if (infos->ast)
		ft_free_ast(infos->ast);
	if (infos->tokens)
		ft_free_token(infos->tokens);
	if (infos->input)
		free(infos->input);
}

void	ft_finish(t_env *infos)
{
	printf("exit\n");
	free_tab(infos->env);
	free_tab(infos->export);
}

int	ft_status_value(t_env *infos)
{
	if (g_signal == 130 || g_signal == 131)
	{
		infos->status = g_signal;
		g_signal = 0;
	}
	else
		infos->status = ft_execute(infos->ast, infos);
	return (infos->status);
}
