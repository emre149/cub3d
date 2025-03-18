/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:02:06 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 13:38:39 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_or_edge(char **map, int i, int j)
{
	if (i < 0 || j < 0 || !map[i] || j >= (int)ft_strlen(map[i])
		|| map[i][j] == ' ')
		return (1);
	return (0);
}

static int	check_direction(char **map, int i, int j, int dir[2])
{
	int	new_i;
	int	new_j;

	new_i = i + dir[0];
	new_j = j + dir[1];
	if (is_empty_or_edge(map, new_i, new_j))
		return (0);
	return (1);
}

int	is_surrounded(char **map, int i, int j)
{
	int	directions[8][2];
	int	k;

	set_directions(directions);
	k = 0;
	while (k < 8)
	{
		if (!check_direction(map, i, j, directions[k]))
		{
			printf("Error:\n Carte non fermée en position [%d,%d].\n", i, j);
			return (0);
		}
		k++;
	}
	return (1);
}

static int	check_line_closed(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == '0')
		{
			if (!is_surrounded(map, i, j))
				return (0);
		}
		j++;
	}
	return (1);
}

int	check_map_closed(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!check_line_closed(map, i))
			return (0);
		i++;
	}
	return (1);
}
