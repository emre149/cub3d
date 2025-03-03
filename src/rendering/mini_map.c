/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:28:31 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/03 18:09:18 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_map_square(t_map_info *data, int x, int y, int color)
{
	int	dx;
	int	dy;

	dy = 0;
	while (dy < MINI_MAP_SCALE)
	{
		dx = 0;
		while (dx < MINI_MAP_SCALE)
		{
			mlx_pixel_put(data->mlx, data->win, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_player_dot(t_map_info *data, int player_x, int player_y)
{
	int	dx;
	int	dy;

	dx = -2;
	while (dx <= 2)
	{
		dy = -2;
		while (dy <= 2)
		{
			mlx_pixel_put(data->mlx, data->win, player_x + dx, player_y + dy,
				0xFF0000);
			dy++;
		}
		dx++;
	}
}

static int	select_map_color(char tile)
{
	if (tile == '1')
		return (0xFFFFFF);
	else if (tile == '0')
		return (0x444444);
	else
		return (0x000000);
}

static void	draw_map_row(t_map_info *data, t_map_info *map_info, int i, int y)
{
	int	j;
	int	x;
	int	color;

	x = 10;
	j = 0;
	while (map_info->map[i][j])
	{
		color = select_map_color(map_info->map[i][j]);
		draw_map_square(data, x, y, color);
		x += MINI_MAP_SCALE;
		j++;
	}
}

void	draw_mini_map(t_map_info *data, t_map_info *map_info)
{
	int	i;
	int	y;

	y = 10;
	i = 0;
	while (map_info->map[i])
	{
		draw_map_row(data, map_info, i, y);
		y += MINI_MAP_SCALE;
		i++;
	}
	draw_player_dir(data, map_info);
}
