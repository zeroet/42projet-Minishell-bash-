/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:06:29 by seyun             #+#    #+#             */
/*   Updated: 2022/02/06 18:02:42 by seyun            ###   ########.fr       */
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
	int token;
	char *str;
}		t_token;

typedef struct s_token_info
{
	int count;
	t_token *token;
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

/********** signal **********/

void	set_signal(void);	

#endif
