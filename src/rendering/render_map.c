/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:17:14 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 15:34:34 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_square(t_map_info *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		while (j < 10)
		{
			mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_map(t_map_info *map_info)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	y = 50;
	while (map_info->map[i])
	{
		x = 50;
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == '1')
				draw_square(map_info, x, y, 0xFFFFFF);
			else if (map_info->map[i][j] == '0')
				draw_square(map_info, x, y, 0x000000);
			x += 10;
			j++;
		}
		y += 10;
		i++;
	}
}
