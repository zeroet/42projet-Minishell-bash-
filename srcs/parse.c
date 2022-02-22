/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyun <seyun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:18:21 by seyun             #+#    #+#             */
/*   Updated: 2022/02/23 00:03:19 by eyoo             ###   ########.fr       */
/*   Updated: 2022/02/07 20:11:13 by eyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		double_quote(char *line, int i)
{
	while (line[i] != '\0')
	{
		i++;
		if (line[i] == '\\' && line [i + 1] == '\"')
			i++;
		else if (line[i] == '\"')
		{
			return (i);
		}
	}
	return (-1);
}

int		single_quote(char *line, int i)
{
	while (line[i] != '\0')
	{
		i++;
		if (line[i] == '\\' && line[i + 1] == '\'')
			i++;
		else if (line[i] == '\'')
		{	
			return (i);
		}
	}
	return (-1);
}

int		check_end_quote(char *line, int i, t_token *token)
{
	if (line[i] == '\"')
	{	
		i = double_quote(line, i);
		if (i == -1)
			return (-1);
		if (token != NULL)
			token->type = T_DOUBLE_QUOTES;
		return (i);
	}
	else if (line[i] == '\'')
	{	
		i = single_quote(line, i);
		if (i == -1)
			return (-1);
		if (token != NULL)
			token->type = T_SINGLE_QUOTES;
		return (i);
	}
	return (-1);
}

void	counting_while(char *line, int *i, int *count)
{
	if (ft_isspace(line[*i]))
		(*i)++;
	else if(line[*i] == '\'' || line[*i] == '\"')
	{
		*i = check_end_quote(line, *i, NULL);
		if (*i != -1)
		{
			(*i)++;
			(*count)++;
		}
	}
	else
	{
		while (!ft_isspace(line[*i]) && line[*i] != '\0')
		{
			if (line[*i] == '\'' || line[*i] == '\"')
				break ;
			(*i)++;
		}
		(*count)++;
	}
}

// fn value 에 token type 값 넣어야함  " ' type 의 경우 4 or 5
int		counting_token(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{	
		counting_while(line, &i, &count);
		if (i == -1)  // " or ' 가 닫히지 않았을 경우 -1 
			return (-1);
	}
	return (count);
}

int		tokenizer(char *line, t_token_info *token_info)
{
	if (*line == '\0')
		return (-1);
	token_info->count = counting_token(line);
	if (token_info->count == -1)
		return (-1);
	token_info->tokens = (t_token *)malloc(sizeof(t_token) * (token_info->count + 1));
	if (token_info->tokens == NULL)
		return (-1);
	token_info->tokens = split_token(line, token_info->count, token_info->tokens);
		
return (token_info->count);
}

int		lexical_analyser(t_list *env, char *line, t_token_info *token_info)
{
	int count;

	count = 0;
	count = tokenizer(line, token_info);
	if (count == -1)
	{
		g_return = 258;
		ft_putendl_fd("fail to lexical analysis", STDERR_FILENO);
		return (-1);
	}
	check_token_env(env, token_info);
	set_token_type(token_info);
	for(int i =0; i < token_info->count; i++)
	{
		printf("%d ---token type || %s ---token str\n", token_info->tokens[i].type, token_info->tokens[i].str);
	}
	return (count);
}

int		syntax_analyser(const t_token_info tokens, t_tree **root)
{
	int	idx;

	idx = pipeline_check(tokens, 0);
	if (idx == -1)
	{
		exit(EXIT_FAILURE);
	}
	idx = set_syntax_pipeline(tokens, 0, root);
	printf("set_syntax_pipeline last idx %d\n", idx);
	return (idx);
}

void	parse(t_list *env, char *line)
{
	t_token_info tokens;
	t_tree		*root;
	int			count;
	int			idx;

	count = 0;
	count = lexical_analyser(env, line, &tokens);
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
