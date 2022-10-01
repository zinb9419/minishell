/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visitor_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 23:13:07 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/02 00:03:33 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_opendir(t_node **node, char *s, int i, char **list)
{
	DIR				*dp;
	struct dirent	*dirp;
	char			*patern;

	dp = opendir(s);
	if (dp == NULL)
	{
		printf("Cannot open directory '%s'\n", s);
		return ;
	}
	dirp = readdir(dp);
	patern = find_patern((*node)->param[i]);
	while (dirp != 0)
	{
		if (dirp->d_name[0] != '.')
		{
			if (wild_card_matching(patern, dirp->d_name, \
			ft_strlen(patern), ft_strlen(dirp->d_name)))
				new_expand_param(list, dirp->d_name);
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
		str++;
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

void	expand_wildcards(t_node **node)
{
	int				i;
	char			*s;
	char			*s1;
	char			**list;

	i = 0;
	while ((*node)->param[i] != 0)
	{
		if ((*node)->exd_p[i][0] == '1' && ft_fndc((*node)->param[i], '*'))
		{
			s1 = ft_strrrchr((*node)->param[i], '/');
			if (ft_fndc(s1, '*'))
			{
				free(s1);
				return ;
			}
			s = ft_strjoin("./", s1);
			ft_opendir(node, s, i, list);
			free(s);
			free(s1);
		}
		i++;
	}
}

void	wild_card(t_node *node)
{
	t_node	*tmp;

	tmp = node;
	while (tmp->type != NODE_EOF)
	{
		if (tmp->type == NODE_CMD && check_inlist_expand(tmp))
			expand_wildcards(&tmp);
		tmp = tmp->next;
	}
}
