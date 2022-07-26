/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibentour <ibentour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:49:47 by ibentour          #+#    #+#             */
/*   Updated: 2022/10/18 22:07:19 by ibentour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_chars(char *arg)
{
	int		ch;

	ch = 0;
	if (arg && !ft_isalpha(arg[0]) && arg[0] != '_')
	{
		print_export_error(arg);
		g_vars.exit_code = 1;
		return (1);
	}
	while (arg && arg[ch] != '\0' && arg[ch] != '=')
	{
		if ((!(ft_isalnum(arg[ch])) && arg[ch] != '_' && arg[ch] != '+') \
			|| (arg[ch] == '+' && arg[ch + 1] != '='))
		{
			print_export_error(arg);
			g_vars.exit_code = 1;
			return (1);
		}
		ch++;
	}
	return (0);
}

static int	what_to_do(t_builtins *tl, char *att, char *arg)
{
	if (ft_strcmp(att, tl->tmp->env_att) == 0)
	{
		if (arg[tl->i] && arg[tl->i] == '=' && arg[tl->i - 1] != '+')
		{
			if (tl->tmp->env_val)
				free(tl->tmp->env_val);
			tl->tmp->env_val = ft_strdup(arg + tl->i + 1);
		}
		else if (arg[tl->i] && arg[tl->i] == '=' && arg[tl->i - 1] == '+')
		{
			tl->val_p = tl->tmp->env_val;
			if (!tl->tmp->env_val)
				tl->tmp->env_val = ft_strdup(arg + tl->i + 1);
			else
				tl->tmp->env_val = ft_strjoin(tl->tmp->env_val, (arg + \
														tl->i + 1));
			free (tl->val_p);
		}
		return (1);
	}
	return (0);
}

static	int	w_env_exist(char *att, char *arg, size_t i)
{
	t_builtins	tl;

	tl.val_p = 0;
	tl.i = i;
	tl.tmp = g_vars.env;
	while (tl.tmp)
	{
		if (what_to_do(&tl, att, arg))
			return (1);
		else
			tl.tmp = tl.tmp->next;
	}
	return (0);
}

int	env_exists(char *arg)
{
	size_t		i;
	char		*att;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i - 1] && arg[i - 1] == '+')
		att = ft_substr(arg, 0, i - 1);
	else
		att = ft_substr(arg, 0, i);
	if (w_env_exist(att, arg, i))
	{
		free (att);
		return (1);
	}
	free(att);
	return (0);
}

void	ft_export(char	**arg, int out)
{
	int		i;

	i = -1;
	g_vars.exit_code = 0;
	if (!arg || arg[0] == '\0')
		print_export(out);
	else
		while (arg[++i])
			export_values(arg[i]);
}
