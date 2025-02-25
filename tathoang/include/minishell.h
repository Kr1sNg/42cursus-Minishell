/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:56:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/24 13:05:49 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>



/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/


/* tokenizer */

typedef enum e_token_type
{
	TK_WORD, // BUILTIN, OPTION, EXTEND, // -n, $, text, echo, cd, pwd, export, unset, env, exit
	TK_SUBSHELL_OPEN, // (
	TK_SUBSHELL_CLOSE, // )
	TK_AND, // &&
	TK_OR, // ||
	TK_PIPE, // |
	TK_REDIR_IN, // <
	TK_REDIR_OUT, // >
	TK_APPEND_OUT, // >>
	TK_HEREDOC, // <<
	TK_DQUOTE, // "all the words in double quote"
	TK_SQUOTE, // 'all the words in single quote'
}	t_token_type;


typedef struct s_token
{
	t_token_type	type;
	char			*word;
	struct s_token	*next;
}	t_token;


/* command trees */

typedef enum e_ast_type
{
	AST_CMD, // commands
	AST_SUBSHELL, // inside parenthesis ( )
	AST_LOGICAL, // || or &&
	AST_PIPE, // |
	AST_REDIRECT, // > < >> <<
}	t_ast_type;

/* structure of Abstract Syntax Tree
	- each node represents either a command or an operator that combines commands
	- using recursive desent parser */

typedef struct s_ast_cmd
{
	t_ast		*cmd;
	char		**args;
}	t_ast_cmd;

typedef struct s_ast_subshell
{
	t_ast		*child;
}	t_ast_subshell;

typedef struct s_ast_logical
{
	t_token_type	*logical; // && or ||
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast_logical;

typedef struct s_ast_pipeline
{
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast_pipeline;

typedef struct s_ast_redirect
{
	t_token_type	direction; // TK_REDIR_IN, TK_REDIR_OUT, TK_APPEND_OUT, or TK_HEREDOC
	struct s_ast	*child;
	char			*filename;
}	t_ast_redirect;

// union: only one value in union exist.

typedef struct s_ast
{
	t_ast_type		type;
	union u_ast_data
	{
		t_ast_cmd		cmd;
		t_ast_subshell	subshell;
		t_ast_logical	logical;
		t_ast_pipeline	pipeline;
		t_ast_redirect	redirect;
	} t_ast_data;	
}	t_ast;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* split */

char	**ft_split_tokens(char *str);

/* tokenize */

t_token	*ft_tokenize(char *input);
t_token	*ft_create_token(char *input);
void	ft_token_add_back(t_token **head, char *input);
void	ft_free_token(t_token *head);

void	ft_print_token(t_token *head);

/* lexing */

int	ft_token_type(char *s);

/* parsing */


/* signal */
void	ft_handler(int sig);


/* error */
void	ft_error_input(int er);



#endif