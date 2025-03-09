/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:30:38 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/09 09:30:41 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/buildins.h"

// int	ft_exec_redir(t_ast_redirect *ast)
// {
// 	int	status;

// 	status = 1;
// 	if (!ast)
// 		return (1);
// 	if (ast->direction == TK_REDIR_IN || ast->direction == TK_HEREDOC)
// 		status = ft_redir_input(ast);
// 	else if (ast->direction == TK_REDIR_OUT)
// 		status = ft_redir_output(ast);
// 	else if (ast->direction == TK_APPEND_OUT)
// 		status = ft_append_output(ast);
// 	return (status);
// }

// int	ft_redir_input(t_ast_redirect *ast)
// {
// 	int	input_fd;
// 	int	original_stdin;
// 	int	status;

// 	input_fd = open(ast->target, O_RDONLY);
// 	if (input_fd == -1)
// 		return (perror(ast->target), EXIT_FAILURE);
// 	original_stdin = dup()
// }
