/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:59:06 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/12 21:24:25 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

extern sig_atomic_t	g_signal_value;

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/



void	cmd_create_env(t_env *infos, char **env);
void	cmd_create_export(t_env *infos);
int		ft_exec_export(char **cmd, t_env *infos);
int		ft_exec_env(char **cmd, char **env);
int		ft_exec_pwd(void);
int		ft_exec_cd(char **cmd, t_env *infos);
int		ft_exec_unset(char **cmd, t_env *infos);
int		ft_exec_echo(char **cmd, t_env *infos);
void	ft_display_export(char **env);
int		ft_strlen_name_env(char *str);
int		check_egal(char *cmd);
char	**cmd_env_unset(char **env, char *cmd);
char	**cmd_add_env(char **env, char *cmd);
char	**cmd_add_export(char **env, char *cmd);
void	cmd_export(t_env *infos, char *cmd);
void	cmd_unset(t_env *infos, char *cmd);
void	free_tab(char **tab);
char	*convert_line_export(char *line);
char	**ft_print_sort_env(char **env);
char	**ft_sort_a(char **env);
char	*check_list_export(char *cmd, char **list);
int		ft_valide_export_cmd(char *cmd);
int		check_egal(char *cmd);
void	ft_swap(char **str, char **str2);
char	*var_export_only(char *line);

int		ft_check_valide_cmd(char *cmd, t_env infos);
void	ft_child(char **cmd, char **env);

int		check_env_var(char *cmd, t_env *infos);
char	*ft_getenv(char *name, char **env);
char	*ft_getpath(char *name, char **path);
char	*ft_strjoin_pipex(char const *s1, char const *s2, char *sep);
char	*ft_strcat_pipex(char *dest, char *src);
int		ft_open(char *name, int rw);
char	*ft_findname(char *name);
void	ft_free_tab(char **tab);
int		ft_manage_pipe(char **cmd, char **env);
void	ft_child(char **cmd, char **env);
int		ft_exec_cmd(char **cmd, t_env *infos);
char	*value_env(char *name, t_env *infos);
void	ft_var_env(char *str, t_env *infos);
int		check_list_var(char *cmd, t_env *infos, int free_old);
int		ft_check_valid_export(char *cmd);
char	**ft_convert_cmd(char **str);
char	*ft_convert_cmd_only(char *str);
int		ft_check_buildins_out_echo(char *cmd);



// int	main(int argc, char *argv[], char *env[]);

void ft_free_cmd(t_env *infos);


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
void	ft_signal(int signum, void (*handler)(int));
void	ft_signal_main(void);
void	ft_signal_child(void);
void	sigint_prompt(int signum);
void	ft_signal_input(void);


/* error */
void	ft_error_syntax(char *s);
void	ft_error_target(char *s);

/* execute follow the tree */
int		ft_execute(t_ast *ast, t_env *env);
int		ft_exe_logical(t_ast_logical *ast, t_env *env);
int 	ft_exe_expression(t_ast_expression *ast, t_env *env);

// --just for testing ast rightnow--
int	ft_exe_pipeexpr(t_ast_pipeexpr *ast, t_env *env);
int ft_exe_subshell(t_ast_subshell *ast, t_env *env);
int ft_exe_command(t_ast_command *ast, t_env *env);
int	ft_exe_words(t_ast_words *ast, t_env *env);
int	ft_exe_redirect(t_ast *ast, t_env *env);

void	ft_close_io(t_env *env);

int ft_exit(char **cmd, t_env *infos);

int		ft_check_star(char * str);
char	*ft_replace_cmd_only(char *cmd);
char	**ft_check_wildcards(char **cmd, t_env *env);
// int		ft_true_false(char *t);

int	ft_here_doc(char *eof);

#endif
