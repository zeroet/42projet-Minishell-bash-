/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:06:29 by seyun             #+#    #+#             */
/*   Updated: 2022/02/09 22:41:18 by seyun            ###   ########.fr       */
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

# define D_YES 0
# define D_NO -1
# define D_QUESTION 1
# define D_ENV 2
# define D_VOID 3

typedef struct s_token
{
	int type;
	int dollar;
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


/******** env_check *******/

void	env_check(t_token_info *token_info);

/******* set_token_type *****/

void	set_token_type(t_token_info *token_info);



#endif
