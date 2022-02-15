/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:18:21 by seyun             #+#    #+#             */
/*   Updated: 2022/02/15 23:05:05 by seyun            ###   ########.fr       */
/*   Updated: 2022/02/07 20:11:13 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexical_analyser(t_list *env, char *line, t_token_info *token_info)
{
	int count;

	count = 0;
	count = tokenizer(line, token_info);
	if (count == -1)// malloc fail or quote fail
		return (-1);
	convert_env(token_info, env); // malloc error 
	set_token_type(token_info);
	for(int i = 0; i < token_info->count; i++)
		printf("%d ---token type || %s ---token str\n", token_info->tokens[i].type, token_info->tokens[i].str);
	return (count);
}

void	parse(t_list *env, char *line)
{
	t_token_info	tokens;
	t_ast			*root;
	int				count;
	int				idx;

	root = NULL;
	count = 0;
	idx = 0;
	count = lexical_analyser(env, line, &tokens); // malloc fail or quote error 
	idx = syntax_analyser(tokens, &root); 
	if (count == -1)
		printf("*************count -1***************\n");	
	else
		printf("************token %d ***************\n", count);
	if (idx == -1)
		printf("index -1\n");
	else
		printf("size of node = %d\n", idx);
	return ;
}
