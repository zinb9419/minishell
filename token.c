/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibentour <ibentour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:17:33 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/18 22:07:19 by ibentour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = (t_token *)malloc(1 * sizeof(t_token));
	if (!token)
		return (0);
	token->type = type;
	token->value = value;
	token->next = (void *)0;
	token->prev = (void *)0;
	return (token);
}

t_token	*get_last_token(t_token *token)
{
	t_token	*lst;

	lst = 0;
	while (token)
	{
		lst = token;
		token = token->next;
	}
	return (lst);
}

void	print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("type %d val {{'%s'}}\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

void	add_last_token(t_token **tokens, t_token *token)
{
	t_token	*lst;

	if (tokens && *tokens)
	{
		lst = get_last_token(*tokens);
		lst->next = token;
		token->prev = lst;
	}
	if (!*tokens)
		*tokens = token;
}
