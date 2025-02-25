/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:56:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/25 21:05:37 by tat-nguy         ###   ########.fr       */
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
	TK_EOF,  // avoid error for next_token and peek_token
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*word;
	struct s_token	*next;
}	t_token;


/* parsing support */
typedef struct s_parser
{
	t_token	*tokens;
	int		index;
	int		token_count;
}	t_parser;


/* command trees */

typedef enum e_ast_type
{
	AST_REDIRECT, // > < >> <<
	AST_WORDS, // words: echo, hello,...
	AST_COMMAND, // words + redirect
	AST_EXPRESSION, // command (+ parenthesis)
	AST_PIPELINE, // |
	AST_LOGICAL, // || or &&	
}	t_ast_type;

/* structure of Abstract Syntax Tree
	- each node represents either a command or an operator that combines commands
	- using recursive desent parser */

//<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }
typedef struct s_ast_redirect
{
	t_token_type			direction; // TK_REDIR_IN, TK_REDIR_OUT, TK_APPEND_OUT, or TK_HEREDOC
	char					*target; // filename or hereend
	struct s_ast_redirect	*next;
}	t_ast_redirect;

//<CMD_WORDS>       	::= <WORD> { <WORD> }
//                    | <ASSIGNMENT_WORD> { <WORD> }
typedef struct s_ast_words
{
	char	**args;
}	t_ast_words;

//<COMMAND>         	::= [ <REDIR_LIST> ] <CMD_WORDS> [ <REDIR_LIST> ]
typedef struct s_ast_command
{
	struct s_ast	*cmd_words;
	struct s_ast	*redirect_list; // list of redirect
} t_ast_command;

//<EXPRESSION>     	::= <COMMAND>  -> type NO_PARENTHESE
//                  | "(" <LOGICAL> ")" -> type PARENTHESE
typedef struct s_ast_expression
{
	struct s_ast	*logical; // only for PARENTHESIS else we use direct ust_command
}	t_ast_expression;

//<PIPELINE>       	::= <EXPRESSION> { "|" <EXPRESSION> }
typedef struct s_ast_pipeline
{
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast_pipeline;

//<LOGICAL>       	::= <PIPELINE> { ("&&" | "||") <PIPELINE> } 
typedef struct s_ast_logical
{
	t_token_type	logical; // && or ||
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast_logical;

//<COMMAND_LINE>    	::= <LOGICAL>
// union: only one value in union exist.
typedef struct s_ast
{
	t_ast_type		type;
	union
	{
		t_ast_redirect		redirect;
		t_ast_words			cmd_words;
		t_ast_command		command;
		t_ast_expression	expression;
		t_ast_pipeline		pipeline;
		t_ast_logical		logical;		
	} u_ast_data;
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
// - parsing support functions:
t_token	*ft_next_token(t_parser *parser);
t_token	*ft_peek_token(t_parser *parser);

/* signal */
void	ft_handler(int sig);


/* error */
void	ft_error_input(int er);



#endif