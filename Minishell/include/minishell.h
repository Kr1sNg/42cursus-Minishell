/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:56:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 15:21:42 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef enum s_file
{
	READ,
	WRITE,
	APPEND,
}	t_file;

typedef struct s_init
{
	int	i;
	int	j;
	int	k;
	int	l;
}	t_init;

typedef struct s_args
{
	char	*path;
	char	**cmd;
	char	**env;
}	t_args;

/* tokenizer */
typedef enum e_token_type
{
	TK_WORD, // BUILTIN, OPTION, EXTEND, // -n, $, text, echo, cd, export...
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
	// TK_EOF,  // avoid error for next_token and peek_token
}	t_ktype;

typedef struct s_token
{
	t_ktype			type;
	char			*word;
	struct s_token	*next;
	int				print_error_syntax;
}	t_token;

/* command trees */
typedef enum e_ast_type
{
	AST_REDIRECT, // > < >> <<
	AST_WORDS, // words: echo, hello,...
	AST_COMMAND, // redirect + words + redirect
	AST_SUBSHELL, // "(logical)" + redirect
	AST_EXPRESSION, // command (or subshell)
	AST_PIPEEXPR, // cmd1 | cmd2
	AST_LOGICAL, // pipe1 || pipe2 or &&	
}	t_ast_type;

/* structure of Abstract Syntax Tree
	- each node represents either a command or an operator that combines commands
	- using recursive desent parser */

//<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }
typedef struct s_ast_redirect //node of redirect_list
{
	t_ktype			direction; // TK_REDR_IN,TK_REDR_OUT,TK_APND_OUT,TK_HDOC
	char			*target; // filename or hereend
	struct s_ast	*next; // redirect_list
}	t_ast_redirect;

//<CMD_WORDS>       	::= <WORD> { <WORD> }
typedef struct s_ast_words
{
	char	**args;
}	t_ast_words;

//<COMMAND>         	::= [ <REDIR_LIST> ] <CMD_WORDS> [ <REDIR_LIST> ]
typedef struct s_ast_command
{
	struct s_ast	*cmd_words;
	struct s_ast	*redirect_list; // list of redirect both ahead and behind
}	t_ast_command;

//<SUBSHELL>          ::= "(" <LOGICAL> ")" [ <REDIR_LIST> ]
typedef struct s_ast_subshell
{
	struct s_ast	*logical;
	struct s_ast	*redirect_list;
}	t_ast_subshell;

///<EXPRESSION> ::= <COMMAND>  -> type NO_PARENTHESE
//		| <SUBSHELL -> type PARENTHESE => "(" <LOGICAL> ")" [ <REDIR_LIST> ]
typedef struct s_ast_expression
{
	bool			parenthesis; // false - COMMAND or true - SUBSHELL
	struct s_ast	*cmd_or_sub;
}	t_ast_expression;

//<PIPELINE>       	::= <EXPRESSION> { "|" <EXPRESSION> }
typedef struct s_ast_pipeexpr
{
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast_pipeexpr;

//<LOGICAL>       	::= <PIPELINE> { ("&&" | "||") <PIPELINE> } 
typedef struct s_ast_logical
{
	t_ktype			operator; // && or ||
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast_logical;

// union: only one value in union exist.
typedef struct s_ast
{
	t_ast_type		type;
	union
	{
		t_ast_redirect		*redirect;
		t_ast_words			*cmd_words;
		t_ast_command		*command;
		t_ast_subshell		*subshell;
		t_ast_expression	*expression;
		t_ast_pipeexpr		*pipeexpr;
		t_ast_logical		*logical;			
	};
}	t_ast;

typedef struct s_env
{
	char	**env;
	char	**export;
	char	**list_export;
	int		status;
	int		fd_in;
	int		fd_out;
	char	*input;
	t_token	*tokens;
	t_ast	*ast;
}	t_env;

#endif
