/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 22:45:52 by ziloughm          #+#    #+#             */
/*   Updated: 2022/09/30 13:54:22 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	first_part(char *s)
{
	t_token	*token;
	t_node	*node;

	token = lexer(s);
	if (!token || !scann_grammar(token))
		return ;
	node = get_nodes(token);
	open_heredoc_files(node);
	wild_card(node);
	//print_nodess(node);
	free_nodes(node);
	free_tokens(token);
}
