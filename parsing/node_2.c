/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:08:08 by ziloughm          #+#    #+#             */
/*   Updated: 2022/09/25 23:52:09 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_node_param(t_node **node, t_token *token)
{
	char	**param;
	int		i;
	int		j;

	if (!token || token->type == TOKEN_EOF)
		return ;
	i = (int)ft_strsize((*node)->param) + 1;
	param = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	while ((*node)->param && (*node)->param[j])
	{
		param[j] = ft_strdup((*node)->param[j]);
		j++;
	}
	free_dstr((*node)->param);
	param[j] = ft_strdup(token->value);
	param[j + 1] = 0;
	(*node)->param = param;
}

void	check_if_expand(t_node **node, t_token *token)
{
	char	**param;
	int		i;
	int		j;

	if (!token || token->type == TOKEN_EOF)
		return ;
	i = (int)ft_strsize((*node)->param) + 1;
	param = (char **)malloc(sizeof(char *) * (i + 1));
	j = 0;
	while ((*node)->param && (*node)->param[j])
	{
		param[j] = ft_strdup((*node)->param[j]);
		j++;
	}
	free_dstr((*node)->param);
	if (token->type == TOKEN_WORD)
		param[j] = ft_strdup("1");
	else
		param[j] = ft_strdup("0");
	param[j + 1] = 0;
	(*node)->param = param;
}

t_node	*advs_node(t_token **token, t_node *node)
{
	if ((*token)->next)
		(*token) = (*token)->next;
	return (node);
}

t_node	*get_node_wored_cmd(t_token **token)
{
	t_node	*node;

	node = init_node(NODE_CMD, ft_strdup((*token)->value));
	(*token) = (*token)->next;
	while ((*token)->type == TOKEN_WORD || (*token)->type == TOKEN_WORD_EX)
	{
		get_node_param(&node, *token);
		(*token) = (*token)->next;
	}
	return (node);
}

t_node	*get_node_wored_herdoc(t_token **token)
{
	t_node	*node;

	node = init_node(NODE_HEREDOC, ft_strdup("<<"));
	(*token) = (*token)->next;
	if ((*token)->type == TOKEN_WORD || (*token)->type == TOKEN_WORD_EX)
	{
		get_node_param(&node, *token);
		check_if_expand(&node, *token);
		(*token) = (*token)->next;
	}
	return (node);
}