/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:06:10 by ibentour          #+#    #+#             */
/*   Updated: 2022/10/20 16:22:53 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*update_pwd(t_builtins *tl, int out)
{
	t_env			*current_env;
	char			*tmp;
	t_builtins		tp;

	tmp = 0;
	current_env = g_vars.env;
	while (current_env != 0)
	{
		if (ft_strcmp(current_env->env_att, "PWD") == 0)
		{
			tl->old_pwd = ft_strdup(current_env->env_val);
			free(current_env->env_val);
			current_env->env_val = getcwd(tmp, sizeof(tmp));
			return (tl->old_pwd);
		}
		current_env = current_env->next;
	}
	tp.tmp_o = ft_strdup("PWD=");
	tp.to_export[0] = ft_strjoin(tp.tmp_o, getcwd(tmp, sizeof(tmp)));
	tp.to_export[1] = 0;
	ft_export(tp.to_export, out);
	free (tp.tmp_o);
	free (tp.to_export[0]);
	return (0);
}

static int	cd_to_home(void)
{
	char	*home;

	home = get_env_val(g_vars.env, "HOME");
	if (!home)
	{
		ft_putstr_fd(ERR_EXEC, 2);
		ft_putstr_fd("cd: HOME not set \n", 2);
		g_vars.exit_code = 1;
		return (0);
	}
	else
		chdir(home);
	free(home);
	return (1);
}

static	int	check_chdir(char **arg)
{
	if (!arg || !arg[0])
		return (cd_to_home());
	else if (!arg[0][0])
		return (1);
	else if (chdir(arg[0]))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg[0], 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		g_vars.exit_code = 1;
		return (0);
	}
	return (1);
}

void	ft_cd(char	**arg, int out)
{
	t_builtins	tl;

	g_vars.exit_code = 0;
	if (check_chdir(arg))
	{
		tl.new_opwd = update_pwd(&tl, out);
		if (tl.new_opwd)
		{
			tl.tmp_o = ft_strdup("OLDPWD=");
			tl.to_export[0] = ft_strjoin(tl.tmp_o, tl.new_opwd);
			tl.to_export[1] = 0;
			ft_export(tl.to_export, out);
			free (tl.tmp_o);
			free (tl.new_opwd);
			free (tl.to_export[0]);
		}
	}
}
