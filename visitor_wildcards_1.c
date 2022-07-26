/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_wildcards_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:13:07 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/23 21:06:45 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wild_card_matching(char *patern, char *str, int n, int m)
{
	int		**mat;
	int		i;
	int		j;

	mat = init_matrix(m, n);
	i = 0;
	while (++i < (n + 1))
		if (patern[i - 1] == '*')
			mat[0][i] = mat[0][i - 1];
	i = 0;
	while (++i < (m + 1))
	{
		j = 0;
		while (++j < (n + 1))
		{
			if (patern[j - 1] == '*')
				mat[i][j] = (mat[i][j - 1] || mat[i - 1][j]);
			if (patern[j - 1] == str[i - 1])
				mat[i][j] = mat[i - 1][j - 1];
		}
	}
	i = mat[i - 1][j - 1];
	free_mat(mat, m + 1);
	return (i);
}

void	ft_opendir(t_node **node, char *s, int i, char ***list)
{
	DIR				*dp;
	struct dirent	*dirp;
	char			*patern;

	dp = opendir(s);
	if (dp == 0)
		return ;
	dirp = readdir(dp);
	patern = find_patern((*node)->param[i]);
	while (dirp != 0)
	{
		if (dirp->d_name[0] != '.')
		{
			if (wild_card_matching(patern, dirp->d_name, \
			ft_strlen(patern), ft_strlen(dirp->d_name)))
				(*list) = new_expand_param((*list), dirp->d_name, \
				ft_strrrchr((*node)->param[i], '/'));
		}
		dirp = readdir(dp);
	}
	free(patern);
	closedir(dp);
}

int	check_inlist_expand(t_node *node)
{
	char	*str;

	str = ft_strrchr(node->value, '/');
	if (!str)
		str = ft_strdup(node->value);
	else
		str = ft_substr(node->value, 1, ft_strlen(node->value) - 1);
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "pwd") \
	|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env") \
	|| !ft_strcmp(str, "export") || !ft_strcmp(str, "exit"))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

char	**expand_wildcards(t_node **node)
{
	int				i;
	char			*s1;
	char			**list;

	i = 0;
	list = 0;
	while ((*node)->param && (*node)->param[i] != 0)
	{
		s1 = ft_strrrchr((*node)->param[i], '/');
		if ((*node)->exd_p[i][0] == '1' && ft_fndc((*node)->param[i], '*') \
		&& !ft_fndc(s1, '*'))
			check_if_added_elemnt(&list, i, s1, node);
		else
			list = new_expand_param(list, (*node)->param[i], ft_strdup(""));
		free(s1);
		i++;
	}
	return (list);
}

void	wild_card(t_node *node)
{
	t_node	*tmp;
	char	**list;

	tmp = node;
	while (tmp->type != NODE_EOF)
	{
		if (tmp->value && tmp->type == NODE_CMD && check_inlist_expand(tmp))
		{
			list = expand_wildcards(&tmp);
			free_dstr(tmp->param);
			tmp->param = list;
		}
		tmp = tmp->next;
	}
}
