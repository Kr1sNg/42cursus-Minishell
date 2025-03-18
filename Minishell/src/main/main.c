/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/18 12:14:42 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

t_env	ft_initialization(int argc, char **argv, char **env)
{
	t_env	infos;

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
		if (g_signal == SIGINT)
			ft_sigint_main(&infos);
		if ((!infos.input) || !ft_strcmp_exit(infos.input))
		{
			if (infos.input && !ft_strcmp_exit(infos.input))
				infos.status = 0;
			break ;
		}
		add_history(infos.input);
		infos.tokens = ft_tokenize(infos.input);
		infos.ast = ft_parse(infos.tokens);
		infos.status = ft_execute(infos.ast, &infos);
		ft_free_cmd(&infos);
	}
	ft_finish(&infos);
	return (infos.status);
}

/* free ast, tokens, input after each command line */
void	ft_free_cmd(t_env *infos)
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
