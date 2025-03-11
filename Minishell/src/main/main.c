/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/10 20:58:14 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//run with -lreadline

#include "../../include/minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <readline/readline.h>
// #include <readline/history.h>


// void ft_execute(char **args, char **envp)
// {
// 	pid_t pid = fork();
// 	int	status;
	
// 	if (pid == 0)
// 	{
// 		if (execve(args[0], args, envp) == -1)
// 		{
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (pid > 0)
// 	{
// 		waitpid(pid, &status, 0);
// 	}
// 	else
// 		perror("fork");
// }

void	ft_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1); // OK ctr-C
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
	return (infos);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;
	t_env	infos;
	// pid_t	pid;
	//ft_copy_env
	// (void)argc; // we don't really need it rightnow
	// (void)argv; // we don't really need it rightnow

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN); //SIG_IGN: ignore signal - ctr-backflash
	signal(SIGTSTP, SIG_IGN); // SIGTSTP: keyboard stop = EOF
	input = (char *)NULL;
	infos = ft_initialization(argc, argv, env);
	// infos.status = 0;
	while (1)
	{
		input = readline("minishell:~ $ ");
		if (!input) // || !ft_strcmp(input, "exit")) // quand on faire "exit" on dois nettoyer tout avant!
			break ;
		add_history(input); // to save history and move up - down cmd
		tokens = ft_tokenize(input);
		// ft_print_token(tokens);
		ast = ft_parse(tokens);
		infos.status = ft_execute(ast, &infos);
		// infos.fd_in = STDIN_FILENO;
		// infos.fd_out = STDOUT_FILENO;
		// ft_free_ast(ast);
		// ft_free_token(tokens);
		// free(input);
		ft_free_cmd(input, ast, tokens, &infos);
	}
	free_tab(infos.env);
	free_tab(infos.export);
	return (infos.status);
}

/* free ast, tokens, input after each command line */
void ft_free_cmd(char* input, t_ast *ast, t_token *tokens, t_env *infos)
{
	infos->fd_in = STDIN_FILENO;
	infos->fd_out = STDOUT_FILENO;
	ft_free_ast(ast);
	ft_free_token(tokens);
	free(input);
}