/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:56:57 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/18 18:45:40 by tat-nguy         ###   ########.fr       */
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
};


typedef struct s_token
{
	// t_type			type; //  | || && or CMD
	char			*cmd; // 
	char			*option; // path/ -n / 
	// struct s_token	*left;
	struct s_token	*next;
}	t_token;






/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

/* tokenize */

t_token	*ft_tokenize(char *input);
t_token	*ft_create_token(char *input);
void	ft_token_add_back(t_token **head, char *input);
void	ft_free_token(t_token *head);

void	ft_print_token(t_token *head);


/* parsing */


/* signal */
void	ft_handler(int sig);


#endif