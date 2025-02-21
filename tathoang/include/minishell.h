/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:56:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/21 14:05:02 by tat-nguy         ###   ########.fr       */
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


typedef enum e_token_type
{
	TEXT, // BUILTIN, OPTION, EXTEND, // -n, $, text, echo, cd, pwd, export, unset, env, exit 0
	PARENTHESIS, // ( ) 1
	OPERATOR, //|, ||, && 2
	REDIRECT, // >, <, >>, << 3
	QUOTE, // "  ", ' ' 4
}	t_token_type;

/* structure of Abstract Syntax Tree
	- each node represents either a command or an operator that combines commands
	- using recursive desent parser */
typedef struct s_tree
{
	t_node_type	type;
	char		**argv; // only used if type == NODE_CMD
	struct s_tree	*left; // left subtree (first cmd)
	struct s_tree	*right; // right subtree (second)
	// redirections also ?
}	t_tree;


typedef struct s_token
{
	char			*cmd; // 
	t_token_type	type;
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

/* lexing */

int	ft_token_type(char *s);

/* parsing */


/* signal */
void	ft_handler(int sig);


/* error */
void	ft_error_input(int er);



#endif