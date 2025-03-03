/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_sec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:47:55 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/03 15:48:48 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_newline_pos(t_glist *last_node)
{
	int	i;

	i = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] == '\n')
		i++;
	return (i);
}

static void	create_clean_node(t_glist **clean_node, char *content, int pos)
{
	int	j;

	j = 0;
	while (content[pos])
		(*clean_node)->content[j++] = content[pos++];
	(*clean_node)->content[j] = '\0';
}

static t_glist	*alloc_clean_node(char *content, int pos)
{
	t_glist	*clean_node;
	int		j;

	clean_node = malloc(sizeof(t_glist));
	if (!clean_node)
		return (NULL);
	clean_node->next = NULL;
	j = ft_strlen(&content[pos]);
	clean_node->content = malloc(sizeof(char) * (j + 1));
	if (!clean_node->content)
	{
		free(clean_node);
		return (NULL);
	}
	return (clean_node);
}

void	clean(t_glist **stash)
{
	t_glist	*last_node;
	t_glist	*clean_node;
	int		i;

	if (!stash || !*stash)
		return ;
	last_node = ft_glistlast(*stash);
	i = find_newline_pos(last_node);
	if (last_node->content[i] == '\0')
	{
		free_stash(*stash);
		*stash = NULL;
		return ;
	}
	clean_node = alloc_clean_node(last_node->content, i);
	if (!clean_node)
		return ;
	create_clean_node(&clean_node, last_node->content, i);
	free_stash(*stash);
	*stash = clean_node;
}
