/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:18:21 by seyun             #+#    #+#             */
/*   Updated: 2022/02/28 21:35:52 by eyoo             ###   ########.fr       */
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

int		syntax_analyser(const t_token_info tokens, t_ast **root)
{
	int idx;

	idx = pipeline_check(tokens, 0);
	if (idx == -1)
	{
		printf("pipleline check fail \n");
	}// case -1 free all & return error command not found
	idx = set_syntax_pipeline(tokens, 0, root);
	return (idx);
}

void	parse(t_list *env, char *line)
{
	t_token_info	tokens;
	t_ast			*root;
	int				count;
	int				idx;

	count = 0;
	idx = 0;
	count = lexical_analyser(env, line, &tokens); // malloc fail or quote error 
	if (count == -1)
		return ;
	idx = syntax_analyser(tokens, &root);
	set_path_in_tree(env, root);
//	free_token(&tokens);
//	return (root);
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
