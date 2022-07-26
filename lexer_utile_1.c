/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utile_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibentour <ibentour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:15:14 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/18 22:07:19 by ibentour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_lexer	*init_lexer(char	*content)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (0);
	lexer->i = 0;
	lexer->content = ft_strdup(content);
	lexer->c = content[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer **lexer)
{
	if ((*lexer)->c != '\0' && (*lexer)->i < (int)ft_strlen((*lexer)->content))
	{
		(*lexer)->i += 1;
		(*lexer)->c = (*lexer)->content[(*lexer)->i];
	}
}

void	lexer_skipe_space(t_lexer *lexer)
{
	if (!lexer || !lexer->c)
		return ;
	while (lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(&lexer);
}

t_token	*advs_token(t_lexer *lexer, t_token *token)
{
	lexer_advance(&lexer);
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->i < (int)ft_strlen(lexer->content))
	{
		lexer_skipe_space(lexer);
		if (lexer->c == '|')
			return (lexer_collect_pipe(lexer));
		if (lexer->c == '&')
			return (lexer_collect_and(lexer));
		if (lexer->c == '>')
			return (lexer_collect_great(lexer));
		if (lexer->c == '<')
			return (lexer_collect_less(lexer));
		else
			return (lexer_collect_id(lexer));
	}
	return (init_token(TOKEN_EOF, ft_strdup("end_of_cmd")));
}
