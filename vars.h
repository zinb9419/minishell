/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:40:52 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/20 18:59:25 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef VARS_H
# define VARS_H

//Prompt String
//# define PS1 "\033[0;32mminishell-1.0:~$\033[0;37m "
# define PS1 "minishell-1.0:~$ "
# define PS2 "> "
# define ERR_SYN "syntax error near unexpected token near "
//# define ERR_EXEC "\033[0;31mminishell:\033[0;37m "
# define ERR_EXEC "minishell: "

//Special characters
# define SPCL "&<>$|\'()\"\t "
# define SPCL1 "<>$|\' \"\t"
# define SPCL2 "&<>$|\' \"\t"
# define SPCL3 "$()<>|\' \"\t"

//Heredoce Nmefile
# define TMP_FILE "/tmp/heredoc_tmp_file_"
# define MAX_HERDOC 16

//Elements
typedef struct s_env
{
	char			*env_att;
	char			*env_val;
	struct s_env	*next;
}t_env;

typedef struct s_vars
{
	int			exit_code;
	int			sign;
	int			*pids;
	char		**herdo_files;
	t_env		*env;
}t_vars;

t_vars	g_vars;

#	endif