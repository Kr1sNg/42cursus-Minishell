/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 15:28:40 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	ft_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* env[] is needed for ENV, EXPORT, UNSET */

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
	// char	*input;
	// t_token	*tokens;
	// t_ast	*ast;
	t_env	infos;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN); //SIG_IGN: ignore signal - ctr-backflash
	signal(SIGTSTP, SIG_IGN); // SIGTSTP: keyboard stop = EOF
	infos = ft_initialization(argc, argv, env);
	while (1)
	{
		infos.input = readline("minishell:~ $ ");
		if (!infos.input) // || !ft_strcmp(input, "exit")) // quand on faire "exit" on dois nettoyer tout avant!
			break ;
		add_history(infos.input); // to save history and move up - down cmd
		infos.tokens = ft_tokenize(infos.input);
		// ft_print_token(tokens);
		infos.ast = ft_parse(infos.tokens);
		infos.status = ft_execute(infos.ast, &infos);
		// infos.fd_in = STDIN_FILENO;
		// infos.fd_out = STDOUT_FILENO;
		// ft_free_ast(ast);
		// ft_free_token(tokens);
		// free(input);
		ft_free_cmd(&infos);
	}
	printf("exit\n");
	free_tab(infos.env);
	free_tab(infos.export);
	return (infos.status);
}

/* free ast, tokens, input after each command line */
void ft_free_cmd(t_env *infos)
{
	infos->fd_in = STDIN_FILENO;
	infos->fd_out = STDOUT_FILENO;
	ft_free_ast(infos->ast);
	ft_free_token(infos->tokens);
	free(infos->input);
}