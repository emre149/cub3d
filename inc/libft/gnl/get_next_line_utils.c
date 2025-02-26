/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 04:00:29 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:39:57 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	newline(t_glist *stash)
{
	int		i;
	t_glist	*current;

	if (stash == NULL)
		return (0);
	current = ft_glistlast(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	line_allocation(char **line, t_glist *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

/* Frees the entire stash. */

void	free_stash(t_glist *stash)
{
	t_glist	*current;
	t_glist	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
t_glist	*ft_glistlast(t_glist *lst)
{
    while (lst && lst->next)
        lst = lst->next;
    return (lst);
}