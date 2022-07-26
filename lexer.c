/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibentour <ibentour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:02:44 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/18 22:07:19 by ibentour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *str)
{
	t_lexer	*lex;
	t_token	*token;
	t_token	*tmp;

	lex = init_lexer(str);
	if (!lex)
		return (0);
	tmp = lexer_get_next_token(lex);
	token = tmp;
	while (tmp->type != TOKEN_EOF && tmp->type != TOKEN_ERR)
	{
		tmp = lexer_get_next_token(lex);
		add_last_token(&token, tmp);
	}
	if (tmp->type == TOKEN_ERR)
	{
		get_new_promt(ft_strdup(tmp->value));
		free_tokens(token);
		free_lexer(lex);
		return (0);
	}
	free_lexer(lex);
	return (token);
}
