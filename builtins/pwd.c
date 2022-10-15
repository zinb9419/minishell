/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibentour <ibentour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:16:26 by ibentour          #+#    #+#             */
/*   Updated: 2022/10/15 01:49:04 by ibentour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(void)
{
	char	cwd[256];

	g_vars.exit_code = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		g_vars.exit_code = 1;
		perror("Error : ");
	}
	else
		printf("%s\n", cwd);
}
