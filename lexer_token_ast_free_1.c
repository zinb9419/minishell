/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_ast_free_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 13:22:39 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/23 16:20:33 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_nodes(t_node *nodes)
{
	t_node	*tmp;

	while (nodes)
	{
		tmp = nodes;
		nodes = nodes->next;
		if (tmp->value)
			free(tmp->value);
		free_dstr(tmp->param);
		free_dstr(tmp->exd_p);
		if (tmp->ambg)
			free(tmp->ambg);
		if (tmp->nfound)
			free(tmp->nfound);
		if (tmp->files)
			free(tmp->files);
		free(tmp);
	}
}

void	free_lexer(t_lexer *lex)
{
	free(lex->content);
	free(lex);
}

void	free_mat(int **mat, int m)
{
	int	i;

	i = 0;
	while (i < m)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}
