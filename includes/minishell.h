/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:06:29 by seyun             #+#    #+#             */
/*   Updated: 2022/02/18 00:19:34 by eyoo             ###   ########.fr       */
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

int		g_return;

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

#define	TREE_NULL 0
#define	TREE_PIPE 1
#define	TREE_CMD 2
#define	TREE_SIMPLE_CMD 3
#define	TREE_REDIRECT 4
#define	TREE_IO_REDIRECT 5

typedef	struct	s_tree
{
	char *node;
	t_token *token_value;
	struct t_tree *left;
	struct t_tree *right;
}		t_tree;

typedef struct s_simple_cmd
{
	char	*original;
	char	*file_path;
	char	**argv;
}	t_simple_cmd;

# define INPUT 1 // <
# define OUTPUT 2 // >
# define HERE_DOCUMENTS 3 // <<
# define APPENDING_OUTPUT 4// >>

typedef struct s_redirect
{
	int		type;
	char	*filename;
} t_redirect;

/********** env_create **********/
void	get_env(char **envp, t_list **env);

/********** parse **********/

void	parse(t_list *env, char *line);
int		double_quote(char *line, int i);
int		single_quote(char *line, int i);
int		check_end_quote(char *line, int i, t_token *token);
void	counting_while(char *line, int *i, int *count);
int		counting_token(char *line);

/********** signal **********/

void	set_signal(void);

/******** split_line *********/

t_token *split_token(char *line, int count, t_token *tokens);

/********check token in env file **********/
void	check_token_env(t_list *env, t_token_info *token_info);
void	set_token_type(t_token_info *token_info);


int		pipeline_check(t_token_info tokens, int idx);
int		cmd_check(t_token_info tokens, int idx);
int		redirect_check(t_token_info tokens, int idx);
int		io_redirect_check(t_token_info tokens, int idx);
int		simple_cmd_check(t_token_info tokens, int idx);


int		set_syntax_pipeline(t_token_info tokens, int idx, t_tree **node);
int		set_syntax_cmd(t_token_info tokens, int idx, t_tree **node);
int		set_syntax_redirect(t_token_info, int idx, t_tree **node);
int		set_syntax_io_redirect(t_token_info tokens, int idx, t_tree **node);
int		set_syntax_simple_cmd(t_token_info tokens, int idx, t_tree **node);
int		add_simple_cmd_argv(t_token_info tokens, t_simple_cmd *simple_cmd, int idx);
t_tree	*new_tree(void *item, int type);
int		redirect_type(char *str);

#endif
