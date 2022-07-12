/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongtki <seongtki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:05:03 by seongtki          #+#    #+#             */
/*   Updated: 2022/07/12 10:08:45 by seongtki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <stdio.h>

typedef struct	s_holder
{
	int				fd;
	char			*line;
	struct s_holder	*prev;
	struct s_holder	*next;
}	t_holder;

char	*get_next_line(int fd);
char	*ft_strchr(const char *x, int c);
char	*ft_strndup(const char *s1, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
#endif