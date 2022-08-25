/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ziloughm <ziloughm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:20:51 by ziloughm          #+#    #+#             */
/*   Updated: 2022/08/25 19:37:48 by ziloughm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LIBFT_H
# define LIBFT_H

int	    ft_isalnum(int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t n, size_t s);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcat(void *dest, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

#	endif