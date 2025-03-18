/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:49:10 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 16:26:04 by ededemog         ###   ########.fr       */
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

static void	init_line_params(t_line_params *params, t_point start, t_point end)
{
	params->dx = abs(end.x - start.x);
	params->dy = abs(end.y - start.y);
	if (start.x < end.x)
		params->sx = 1;
	else
		params->sx = -1;
	if (start.y < end.y)
		params->sy = 1;
	else
		params->sy = -1;
	params->err = params->dx - params->dy;
}

void	draw_line_minimap(t_map_info *data, t_point start, t_point end,
		int color)
{
	t_line_params	params;
	int				x0;
	int				y0;

	x0 = start.x;
	y0 = start.y;
	init_line_params(&params, start, end);
	while (1)
	{
		mlx_pixel_put(data->mlx, data->win, x0, y0, color);
		if (x0 == end.x && y0 == end.y)
			break ;
		update_line_coords(&x0, &y0, 2 * params.err, &params);
	}
}

void	draw_player_dir(t_map_info *data, t_map_info *map_info)
{
	t_point	player;
	t_point	dir;

	player.x = 10 + (map_info->pos[X] * MINI_MAP_SCALE);
	player.y = 10 + (map_info->pos[Y] * MINI_MAP_SCALE);
	dir.x = player.x + map_info->dir[X] * MINI_MAP_SCALE / 2;
	dir.y = player.y + map_info->dir[Y] * MINI_MAP_SCALE / 2;
	draw_line_minimap(data, player, dir, 0xFF0000);
	draw_player_dot(data, player.x, player.y);
}
