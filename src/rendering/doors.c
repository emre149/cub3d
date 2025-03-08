/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:53:06 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/08 16:39:23 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_doors(t_map_info *map_info)
{
	int	i;
	int	j;

	map_info->door_count = 0;
	i = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == DOOR_CLOSE)
			{
				map_info->door_state[map_info->door_count][0] = j;
				map_info->door_state[map_info->door_count][1] = i;
				map_info->door_timer[map_info->door_count] = 0.0;
				map_info->door_count++;
			}
			j++;
		}
		i++;
	}
	printf("Found %d doors in map\n", map_info->door_count);
}

int	is_door(t_map_info *map_info, int x, int y)
{
	if (x < 0 || y < 0 || !map_info->map[y]
		|| x >= (int)ft_strlen(map_info->map[y]))
		return (0);
	return (map_info->map[y][x] == DOOR_CLOSE
		|| map_info->map[y][x] == DOOR_OPEN);
}

int	is_door_closed(t_map_info *map_info, int x, int y)
{
	if (x < 0 || y < 0 || !map_info->map[y]
		|| x >= (int)ft_strlen(map_info->map[y]))
		return (0);
	return (map_info->map[y][x] == DOOR_CLOSE);
}

int	find_door_index(t_map_info *map_info, int x, int y)
{
	int	i;

	i = 0;
	while (i < map_info->door_count)
	{
		if (map_info->door_state[i][0] == x && map_info->door_state[i][1] == y)
			return (i);
		i++;
	}
	return (-1);
}

void	toggle_door(t_map_info *map_info, int x, int y)
{
	int	door_idx;

	door_idx = find_door_index(map_info, x, y);
	if (door_idx != -1)
	{
		if (map_info->map[y][x] == DOOR_CLOSE)
		{
			map_info->map[y][x] = DOOR_OPEN;
			printf("Door opened at position [%d,%d]\n", x, y);
		}
		else if (map_info->map[y][x] == DOOR_OPEN)
		{
			map_info->map[y][x] = DOOR_CLOSE;
			printf("Door closed at position [%d,%d]\n", x, y);
		}
	}
}

void	interact_with_door(t_map_info *map_info)
{
	int	target_x;
	int	target_y;

	target_x = (int)(map_info->pos[X] + map_info->dir[X]);
	target_y = (int)(map_info->pos[Y] + map_info->dir[Y]);
	if (is_door(map_info, target_x, target_y))
	{
		toggle_door(map_info, target_x, target_y);
	}
	else
	{
		printf("No door to interact with\n");
	}
}

