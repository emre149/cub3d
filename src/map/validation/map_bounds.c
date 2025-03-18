/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bounds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:01:01 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 13:01:18 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_bounds(char **map, int *start, int *end)
{
	int	i;

	i = 0;
	*start = -1;
	*end = -1;
	while (map[i])
	{
		if (is_map_line(map[i]))
		{
			if (*start == -1)
				*start = i;
			*end = i;
		}
		i++;
	}
	if (*start == -1)
		return (0);
	return (1);
}

char	**duplicate_map_lines(char **map, int start, int end)
{
	char	**new_map;
	int		i;
	int		j;

	new_map = malloc(((end - start) + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = start;
	j = 0;
	while (i <= end)
	{
		new_map[j] = ft_strdup(map[i]);
		if (!new_map[j])
		{
			free_map(new_map);
			return (NULL);
		}
		i++;
		j++;
	}
	new_map[j] = NULL;
	return (new_map);
}
