/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:56:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/03 22:14:18 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include "../libft/includes/libft.h"
# include "buildins.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>


/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/

typedef struct s_env t_env;

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
	// TK_EOF,  // avoid error for next_token and peek_token
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*word;
	struct s_token	*next;
}	t_token;


// /* parsing support */
// typedef struct s_parser
// {
// 	t_token	*tokens;
// 	int		index;
// 	int		token_count;
// }	t_parser;


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
	t_token_type	direction; // TK_REDIR_IN, TK_REDIR_OUT, TK_APPEND_OUT, or TK_HEREDOC
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

///<EXPRESSION>     	::= <COMMAND>  -> type NO_PARENTHESE
//						| <SUBSHELL -> type PARENTHESE => "(" <LOGICAL> ")" [ <REDIR_LIST> ]
typedef struct s_ast_expression
{
	bool				parenthesis; // false - COMMAND or true - SUBSHELL
	struct s_ast		*cmd_or_sub;
	
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
	t_token_type	operator; // && or ||
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



/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

// int	main(int argc, char *argv[], char *env[]);

/* split */

char	**ft_split_tokens(char *str);

/* tokenize */

t_token	*ft_tokenize(char *input);
t_token	*ft_create_token(char *input);
void	ft_token_add_back(t_token **head, char *input);
void	ft_free_token(t_token *head);

void	ft_print_token(t_token *head);

/* lexing */
t_token_type	ft_token_type(char *word);

/* parsing */
// create ast node
void	ft_new_ast_node(t_ast **node, t_ast_type type);
t_ast	*ft_create_ast_redirect(t_token_type direction, char *target);
t_ast	*ft_create_ast_words(char **args);
t_ast	*ft_create_ast_command(t_ast *ahead, t_ast *cmd_words, t_ast *behind);
t_ast	*ft_create_ast_subshell(t_ast *logical, t_ast *redir_list);
t_ast	*ft_create_ast_expression(t_ast *expression, bool parenthesis);
t_ast	*ft_create_ast_pipeexpr(t_ast *left, t_ast *right) ;
t_ast	*ft_create_ast_logical(t_token_type logical, t_ast *left, t_ast *right);

// parsing through level of node
t_ast	*ft_parse(t_token *token);
t_ast   *ft_parse_logical(t_token **token);
t_ast   *ft_parse_pipeexpr(t_token **token);
t_ast   *ft_parse_expression(t_token **token);
t_ast   *ft_parse_command(t_token **token);
t_ast   *ft_parse_subshell(t_token **token);
t_ast   *ft_parse_words(t_token **token);
t_ast   *ft_parse_redirect(t_token **token);

// free ast node
void    ft_free_ast(t_ast *ast);
void    ft_free_logical(t_ast *ast);
void    ft_free_pipeexpr(t_ast *ast);
void    ft_free_expression(t_ast *ast);
void    ft_free_subshell(t_ast *ast);
void    ft_free_command(t_ast *ast);
void    ft_free_words(t_ast *words);
void	ft_free_redir_list(t_ast *redir_list);


// utils support
void	ft_redir_list_add(t_ast **head, t_ast *new);


/* signal */
void	ft_handler(int sig);


/* error */
void	ft_error_input(int er);
void	ft_error_syntax(char *s);

/* execute follow the tree */
int	ft_execute(t_ast *ast, t_env *env);
int	ft_exe_logical(t_ast_logical *ast, t_env *env);
int ft_exe_expression(t_ast_expression *ast, t_env *env);

// --just for testing ast rightnow--
int	ft_exe_pipeexpr(t_ast_pipeexpr *ast, t_env *env);
int ft_exe_subshell(t_ast_subshell *ast, t_env *env);
int ft_exe_command(t_ast_command *ast, t_env *env);
int	ft_exe_words(t_ast_words *ast, t_env *env);
int	ft_exe_redirect(t_ast *ast, int *fd_in, int *fd_out);

#endif