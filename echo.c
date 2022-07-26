/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:25:25 by ibentour          #+#    #+#             */
/*   Updated: 2022/10/20 15:55:03 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	put_args(char **args, t_builtins *tl, int out)
{
	while (args && args[tl->i])
	{
		ft_putstr_fd(args[tl->i], out);
		if (args[tl->i + 1])
			write(out, " ", 1);
		tl->i++;
	}
}

int	ft_echo(char **args, int out)
{
	t_builtins	tl;

	tl.i = 0;
	tl.n_line = 0;
	while (args && args[tl.i] && (ft_strncmp(args[tl.i], "-n", 2) == 0))
	{
		tl.j = 2;
		while (args[tl.i][tl.j] == 'n')
			tl.j++;
		if (args[tl.i][tl.j] != 'n'
						&& args[tl.i][tl.j] != '\0')
			break ;
		else
			tl.n_line++;
		tl.i++;
	}
	put_args(args, &tl, out);
	if (tl.n_line == 0)
		write(out, "\n", 1);
	g_vars.exit_code = 0;
	return (0);
}
