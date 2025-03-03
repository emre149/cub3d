/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:18:26 by emre149           #+#    #+#             */
/*   Updated: 2025/03/03 15:49:42 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_glist
{
	char			*content;
	struct s_glist	*next;
}					t_glist;

char				*get_next_line(int fd);

void				read_to_stash(int fd, t_glist **stash);

int					newline(t_glist *stash);

void				stash_to_line(t_glist *stash, char **line);

void				line_allocation(char **line, t_glist *stash);

void				add(t_glist **stash, char *buf, int already_read);

void				free_stash(t_glist *stash);

t_glist				*ft_glistlast(t_glist *lst);

void				clean(t_glist **stash);

#endif