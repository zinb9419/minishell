/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_collect_double_quote_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibentour <ibentour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 18:38:23 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/18 22:07:19 by ibentour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer_collect_double_quote_fafter(t_lexer *lexer, char *str2)
{
	if (lexer->c == '&' && lexer->content[lexer->i + 1] != '&')
		str2 = lexer_after_single_and(lexer, str2);
	if (lexer->c != '\0' && (lexer->c == '$' || lexer->c == '\'' || \
	!check_spcl_char(SPCL, lexer->c) || lexer->c == '"'))
		return (lexer_collect_double_quote_after(lexer, str2, lexer->c));
	return (init_token(TOKEN_WORD_EX, str2));
}

t_token	*lexer_collect_quote_herdoc_quotes(t_lexer *lexer, char c)
{
	t_token	*token;

	if (!check_close_quote(lexer->content, c, lexer->i + 1))
		token = init_token(TOKEN_ERR, ft_strjoin("Unclosed quote near ", \
		lexer->content + lexer->i));
	else
		token = lexer_collect_quotes_herdoc(lexer, c);
	return (token);
}

t_token	*lexer_collect_quotes_herdoc(t_lexer *lexer, char c)
{
	t_token	*token;
	char	*str;
	char	*str1;

	str = get_herdoc_str(lexer, c);
	if (lexer->c == '$')
		token = lexer_collect_env_herdoc(lexer, "$");
	else if (lexer->c == '"')
		token = lexer_collect_quote_herdoc_quotes(lexer, '"');
	else if (lexer->c == '\'')
		token = lexer_collect_quote_herdoc_quotes(lexer, '\'');
	else if (!check_spcl_char(SPCL, lexer->c))
		token = lexer_collect_env_herdoc(lexer, "");
	else
		token = init_token(TOKEN_WORD_EX, ft_strdup(""));
	if (token->type != TOKEN_ERR)
	{
		str1 = token->value;
		token->type = TOKEN_WORD_EX;
		token->value = ft_strjoin(str, token->value);
		free(str1);
	}
	free(str);
	return (token);
}
