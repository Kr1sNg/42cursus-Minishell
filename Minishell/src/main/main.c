/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/12 21:18:37 by tat-nguy         ###   ########.fr       */
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

	g_signal_value = 0;
	if (argc > 1)
		return (ft_error_target(argv[1]), exit(127), 0);
	// ft_signal_main();
	ft_signal_input();
	// signal(SIGINT, ft_sigint_handler); // ctr-c
	// signal(SIGQUIT, ft_sigquit_handler); //SIG_IGN: ignore signal - ctr-backflash
	infos = ft_initialization(argc, argv, env);
	while (1)
	{
		infos.input = readline("minishell:~ $ ");
		if (!infos.input) // || !ft_strcmp(input, "exit")) // quand on faire "exit" on dois nettoyer tout avant!
			break ;
		add_history(infos.input); // to save history and move up - down cmd
		infos.tokens = ft_tokenize(infos.input);
		infos.ast = ft_parse(infos.tokens);
		infos.status = ft_execute(infos.ast, &infos);
		ft_free_cmd(&infos);
	}
	printf("exit\n");
	free_tab(infos.env);
	free_tab(infos.export);
	if (g_signal_value == SIGINT)
		infos.status = 130;
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