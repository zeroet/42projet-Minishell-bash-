/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:06:29 by seyun             #+#    #+#             */
/*   Updated: 2022/02/17 23:36:12 by seyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <signal.h>
#include "../libft/libft.h"
#include <termios.h>

# define T_NULL 0
# define T_WORD 1
# define T_PIPE 2
# define T_REDIRECT 3
# define T_DOUBLE_QUOTES 4
# define T_SINGLE_QUOTES 5


typedef struct s_token
{
	int type;
	char *str;
}		t_token;

typedef struct s_token_info
{
	int count;
	t_token *tokens;
}	t_token_info;

typedef struct s_env
{
	char *origin;
	char *name;
	char *value;
}		t_env;

#define AST_PIPE 1
#define AST_CMD 2
#define AST_SIMPLE_CMD 3
#define AST_REDIRECT 4
#define AST_IO_REDIRCT 5

typedef struct s_ast_tree
{
	int		type;
	void	*data;
	struct s_ast_tree *left;
	struct s_ast_tree *right;
} t_ast;

typedef struct s_simple_cmd
{
	char *original;
	char *file_path;
	char **argv;
}	t_simple_cmd;

# define INPUT 1
# define OUTPUT 2
# define HERE_DOCUMENTS 3
# define APPENDING_OUTPUT 4

typedef struct s_redirect
{
	int type;
	char *filename;
}	t_redirect;

/* --------------- parse ----------------------*/

void	get_env(char **envp, t_list **env);

void	parse(t_list *env, char *line);
int		double_quote(char *line, int i);
int		single_quote(char *line, int i);
int		check_end_quote(char *line, int i, t_token *token);
void	counting_while(char *line, int *i, int *count);
int		counting_token(char *line);

void	set_signal(void);

int		tokenizer(char *line, t_token_info *token_info);

t_token *split_token(char *line, int count, t_token *tokens);

void	convert_env(t_token_info *token_info, t_list *env);
char		*expand(char *line, int idx, t_list *env);
void	set_new_str(char *new_line, char *substr1, char *env_value, char *substr2);
int		find_dollar(char *str);
int		find_end_dollar(char *str, int idx);
char	*is_env(t_list *env, char *name);

void	set_token_type(t_token_info *token_info);

int		syntax_analyser(const t_token_info tokens, t_ast **root);
int		pipeline_check(t_token_info tokens, int idx);
int		cmd_check(t_token_info tokens, int idx);
int		io_redirect_check(t_token_info tokens, int idx);
int		redirect_check(t_token_info tokens, int idx);
int		simple_cmd_check(t_token_info tokens, int idx);



int	redirect_type(char *str);
t_ast *new_ast(void *item, int type);
int	add_simple_cmd_argv(t_token_info tokens, t_simple_cmd *simple_cmd, int idx);
int	set_syntax_io_redirect(t_token_info tokens, int idx, t_ast **node);
int set_syntax_redirects(t_token_info tokens, int idx, t_ast **node);
int	set_syntax_cmd(t_token_info tokens, int idx, t_ast **node);
int set_syntax_pipeline(t_token_info tokens, int idx, t_ast **node);
int	set_syntax_simple_cmd(t_token_info tokens, int idx, t_ast **node);
int	set_syntax_argv(t_token_info tokens, int idx, char **args, int depth);

#endif
