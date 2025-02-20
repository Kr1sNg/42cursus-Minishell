/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:56:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/20 21:45:09 by tat-nguy         ###   ########.fr       */
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



/*
** :::::::::::::::::::::::::::* STRUCT DECLARATION *::::::::::::::::::::::::: **
*/


/* command trees */

// >$ echo $USER | echo hello && ls

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE, // |
	NODE_AND, // &&
	NODE_OR, // ||
}	t_node_type;

// builtin: echo, cd, pwd, export, unset, env, exit
// quote: " ", ' '
// open: $
// operation: |, ||, &&
// redirect: >, <, >>, <<
// option: -n


typedef enum e_token_type
{
	BUILTIN, // echo, cd, pwd, export, unset, env, exit
	OPERATION, //|, ||, &&
	REDIRECT, // >, <, >>, <<
	TEXT, // text, quote,...
	EXTEND, // $
	OPTION, //-n (only echo)
}	t_token_type;

/* structure of Abstract Syntax Tree
	- each node represents either a command or an operator that combines commands
	- using recursive desent parser */
typedef struct s_ast
{
	t_node_type	type;
	char		**argv; // only used if type == NODE_CMD
	struct s_ast	*left; // left subtree (first cmd)
	struct s_ast	*right; // right subtree (second)
	// redirections also ?
}	t_ast;


typedef struct s_token
{
	char			*cmd; // 
	char			*option; // path/ -n / 
	// struct s_token	*left;
	struct s_token	*next;
}	t_token;






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

/* parsing */


/* signal */
void	ft_handler(int sig);


/* error */
void	ft_error_input(int er);



#endif