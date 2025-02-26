/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:28:31 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/26 11:36:47 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_mini_map(t_data *data, t_map_info *map_info)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;

	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	y = 10;
	i = 0;
	while (map_info->map[i])
	{
		x = 10;
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == '1')
				color = 0xFFFFFF;
			else if (map_info->map[i][j] == '0')
				color = 0x000000;
			else
				color = 0x444444;
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
			x += MINI_MAP_SCALE;
			j++;
		}
		y += MINI_MAP_SCALE;
		i++;
	}
}