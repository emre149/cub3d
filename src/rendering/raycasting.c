/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:59 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 16:26:07 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	calc_wall_texture(t_map_info *map_info, t_draw_data *data)
{
	if (map_info->side == 0)
		data->wall_x = map_info->pos[1] + map_info->wall_dist
			* map_info->ray_dir[1];
	else
		data->wall_x = map_info->pos[0] + map_info->wall_dist
			* map_info->ray_dir[0];
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (double)IMG_SIZE);
	if ((map_info->side == 0 && map_info->ray_dir[0] > 0)
		|| (map_info->side == 1 && map_info->ray_dir[1] < 0))
		data->tex_x = IMG_SIZE - data->tex_x - 1;
}

static void	draw_texture_pixel(t_map_info *map_info, t_draw_data *data,
		int **buff, int x)
{
	int	y;
	int	tex_y;
	int	color;

	data->step = 1.0 * IMG_SIZE / map_info->line_height;
	data->tex_pos = (data->draw_start - SCREEN_HEIGHT / 2
			+ map_info->line_height / 2) * data->step;
	y = data->draw_start;
	while (y < data->draw_end)
	{
		tex_y = (int)data->tex_pos & (IMG_SIZE - 1);
		data->tex_pos += data->step;
		if (map_info->assets[data->tex_num] != NULL)
		{
			color = map_info->assets[data->tex_num][tex_y * IMG_SIZE
				+ data->tex_x];
			if (map_info->side == 1)
				color = (color >> 1) & 0x7F7F7F;
			buff[y][x] = color;
		}
		else
			buff[y][x] = 0xFF00FF;
		y++;
	}
}

void	draw_line(t_map_info *map_info, int **buff, int x)
{
	t_draw_data	data;

	data.draw_start = map_info->draw_start;
	data.draw_end = map_info->draw_end;
	data.tex_num = map_info->tex_num;
	calc_wall_texture(map_info, &data);
	draw_texture_pixel(map_info, &data, buff, x);
}

void	init_ray(t_map_info *map_info, int x)
{
	map_info->camerax[X] = 2 * x / (double)SCREEN_WIDTH - 1;
	map_info->ray_dir[X] = map_info->dir[X] + map_info->plane[X]
		* map_info->camerax[X];
	map_info->ray_dir[Y] = map_info->dir[Y] + map_info->plane[Y]
		* map_info->camerax[X];
	map_info->map_p[X] = (int)map_info->pos[X];
	map_info->map_p[Y] = (int)map_info->pos[Y];
	map_info->ddist[X] = fabs(1 / map_info->ray_dir[X]);
	map_info->ddist[Y] = fabs(1 / map_info->ray_dir[Y]);
}
