/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:11:11 by ziloughm          #+#    #+#             */
/*   Updated: 2022/10/23 13:40:25 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef EXECUTION_H
# define EXECUTION_H

//Util function
int		ft_lstsizecmd(t_cmd *lst);
void	ft_error(char *msg, int i);
int		check_inlist_builtin(char *s);
int		ft_chekc_inputfile(char **str);
int		ft_chekc_ouputfile(char **str, int app);
int		ft_chekc_ouputfile_herdoc(char **str, int app);
void	ft_dup(int fdi, int fdout);
void	ft_clode_fd(int fdi, int fdout);
int		check_builtin_letters(char *s);
char	**new_expand_param2(char **param, char *str);
void	check_directry_err(t_cmd *cmd);
char	*ft_check_path_exist(void);
char	**ft_get_path(void);
int		ft_en_len(void);
char	**ft_get_env(void);
void	ft_exe_cmd(char	*cmd, char **param, char **env);
char	**add_param(char **p, char	*str);
int		check_files_herdoc(t_cmd *cmd);
void	check_files(t_cmd *cmd);
void	ft_execute_cmd(t_cmd *line_cmd);
void	check_ouin_multcmd(t_cmd *line_cmd, int *fdi, int *fdo);

//Bultins execution functions
int		check_builtin(char *builtin);
void	execute_builtin(int x, char **ast_args, int out);

//Util Execute Command
void	ft_execute_cmd(t_cmd *line_cmd);

//Execut Command Line
void	ft_execute_single_cmd(t_cmd *line_cmd);
void	ft_execute_cmd_line(t_cmd *line_cmd);
int		check_execute_builtin(t_cmd *line_cmd);

void	second_part(t_ast *ast);

#	endif