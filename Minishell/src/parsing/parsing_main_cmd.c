/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 15:22:45 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/*<COMMAND>         	::= [ <REDIR_LIST> ] <CMD_WORDS> [ <REDIR_LIST> ]*/

t_ast	*ft_parse_command(t_token **token)
{
	t_ast	*ahead;
	t_ast	*cmd_words;
	t_ast	*behind;

	ahead = ft_parse_redirect(token);
	cmd_words = ft_parse_words(token);
	if (!cmd_words)
		return (ft_free_ast(ahead), NULL);
	behind = ft_parse_redirect(token);
	return (ft_create_ast_command(ahead, cmd_words, behind));
}

/*<SUBSHELL>          ::= "(" <LOGICAL> ")" [ <REDIR_LIST> ]*/

t_ast	*ft_parse_subshell(t_token **token)
{
	t_ast	*logical;
	t_ast	*redir_list;

	redir_list = NULL;
	if (*token && (*token)->type == TK_SUBSHELL_OPEN)
	{
		*token = (*token)->next;
		logical = ft_parse_logical(token);
		if (!logical || !*token || (*token)->type != TK_SUBSHELL_CLOSE)
		{
			ft_free_ast(logical);
			return (ft_error_syntax("(", *token), NULL);
		}
		*token = (*token)->next;
		if (*token)
			redir_list = ft_parse_redirect(token);
		return (ft_create_ast_subshell(logical, redir_list));
	}
	return (ft_error_syntax("(", *token), NULL);
}

/*<CMD_WORDS>       	::= <WORD> { <WORD> }*/

t_ast	*ft_parse_words(t_token **token)
{
	t_token	*current;
	int		argc;
	char	**args;
	int		i;

	current = *token;
	argc = 0;
	while (current && (current->type == TK_WORD || current->type == TK_DQUOTE
			|| current->type == TK_SQUOTE))
	{
		argc++;
		current = current->next;
	}
	if (argc == 0)
		return (NULL);
	args = ft_calloc((argc + 1), sizeof(char *));
	i = 0;
	while (i < argc)
	{
		args[i++] = ft_strdup((*token)->word);
		*token = (*token)->next;
	}
	args[argc] = NULL;
	return (ft_create_ast_words(args));
}

/*<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }
//<REDIRECTION>     	::= (">" | "<" | ">>") <WORD>
//						| "<<" <WORD>
// ex: echo hello "< file1 >> file2 > file3" */

t_ast	*ft_parse_redirect(t_token **token)
{
	t_ast			*head;
	t_ast			*curr;
	t_token_type	direction;
	char			*target;

	head = NULL;
	while (*token && (*token)->next && ((*token)->type == TK_REDIR_IN
			|| (*token)->type == TK_REDIR_OUT || (*token)->type == TK_APPEND_OUT
			|| (*token)->type == TK_HEREDOC))
	{
		direction = (*token)->type;
		*token = (*token)->next;
		if (!(*token) || (*token)->type != TK_WORD)
			return (ft_free_ast(head), NULL);
		target = ft_strdup((*token)->word);
		curr = ft_create_ast_redirect(direction, target);
		if (!curr)
			return (free(target), ft_free_ast(head), NULL);
		if (!head)
			head = curr;
		else
			ft_redir_list_add(&head, curr);
		*token = (*token)->next;
	}
	return (head);
}
