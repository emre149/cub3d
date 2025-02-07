/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:35:09 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/07 15:39:55 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	is_valid_element(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == ' ');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static int	check_surrounding_cells(t_map_info *map_info, int y, int x)
{
	if (y == 0 || y == map_info->map_height - 1 || x == 0
		|| x == map_info->map_width - 1)
		return (0);
	if (!map_info->map[y - 1][x] || !map_info->map[y + 1][x]
		|| !map_info->map[y][x - 1] || !map_info->map[y][x + 1])
		return (0);
	if (map_info->map[y - 1][x] == ' ' || map_info->map[y + 1][x] == ' '
		|| map_info->map[y][x - 1] == ' ' || map_info->map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static int	is_map_elements_valid(t_map_info *map_info, int y, int x)
{
	char	current;

	current = map_info->map[y][x];
	if (!is_valid_element(current))
		return (0);
	if (is_player_char(current))
	{
		if (map_info->player_dir != 0)
			return (0);
		map_info->player_x = x;
		map_info->player_y = y;
		map_info->player_dir = current;
	}
	if (current == '0' || is_player_char(current))
	{
		if (!check_surrounding_cells(map_info, y, x))
			return (0);
	}
	return (1);
}

int	valid_map(t_map_info *map_info)
{
	int x;
	int y;

	if (!map_info->map || !map_info->map[0])
		return (0);
	y = 0;
	while (y < map_info->map_height)
	{
		x = 0;
		while (x < map_info->map_width)
		{
			if (!is_map_elements_valid(map_info, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (map_info->player_dir != 0);
}