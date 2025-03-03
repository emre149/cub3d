/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:49:10 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/03 17:49:23 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	update_line_coords(int *x0, int *y0, int e2, t_line_params *params)
{
	if (e2 > -params->dy)
	{
		params->err -= params->dy;
		*x0 += params->sx;
	}
	if (e2 < params->dx)
	{
		params->err += params->dx;
		*y0 += params->sy;
	}
}

void	draw_line_minimap(t_map_info *data, int x0, int y0, int x1, int y1,
		int color)
{
	t_line_params	params;

	params.dx = abs(x1 - x0);
	params.dy = abs(y1 - y0);
	params.sx = (x0 < x1) ? 1 : -1;
	params.sy = (y0 < y1) ? 1 : -1;
	params.err = params.dx - params.dy;
	while (1)
	{
		mlx_pixel_put(data->mlx, data->win, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		update_line_coords(&x0, &y0, 2 * params.err, &params);
	}
}

void	draw_player_dir(t_map_info *data, t_map_info *map_info)
{
	int	player_x;
	int	player_y;
	int	dir_x;
	int	dir_y;

	player_x = 10 + (map_info->pos[X] * MINI_MAP_SCALE);
	player_y = 10 + (map_info->pos[Y] * MINI_MAP_SCALE);
	dir_x = player_x + map_info->dir[X] * MINI_MAP_SCALE / 2;
	dir_y = player_y + map_info->dir[Y] * MINI_MAP_SCALE / 2;
	draw_line_minimap(data, player_x, player_y, dir_x, dir_y, 0xFF0000);
	draw_player_dot(data, player_x, player_y);
}
