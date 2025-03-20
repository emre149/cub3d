/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:12:51 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/20 21:14:16 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static double	calculate_wall_x(t_map_info *map_info)
{
	double	wall_x;

	if (map_info->side == 0)
		wall_x = map_info->pos[1] + map_info->wall_dist * map_info->ray_dir[1];
	else
		wall_x = map_info->pos[0] + map_info->wall_dist * map_info->ray_dir[0];
	wall_x -= floor(wall_x);
	return (wall_x);
}

static int	calculate_tex_x(t_map_info *map_info, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)IMG_SIZE);
	if (map_info->side == 0 && map_info->ray_dir[0] > 0)
		tex_x = IMG_SIZE - tex_x - 1;
	else if (map_info->side == 1 && map_info->ray_dir[1] < 0)
		tex_x = IMG_SIZE - tex_x - 1;
	return (tex_x);
}

static void	set_line_variables(t_line_data *ld, t_map_info *map_info)
{
	ld->draw_start = map_info->draw_start;
	ld->draw_end = map_info->draw_end;
	ld->tex_num = map_info->tex_num;
	ld->wall_x = calculate_wall_x(map_info);
	ld->tex_x = calculate_tex_x(map_info, ld->wall_x);
	ld->step = 1.0 * IMG_SIZE / map_info->line_height;
	ld->tex_pos = (ld->draw_start - SCREEN_HEIGHT / 2 + map_info->line_height
			/ 2) * ld->step;
}

static void	draw_pixel(t_map_info *map_info, int **buff, t_line_data *ld, int x)
{
	int	color;
	int	tex_y;

	tex_y = (int)ld->tex_pos & (IMG_SIZE - 1);
	ld->tex_pos += ld->step;
	if (map_info->assets[ld->tex_num] != NULL)
	{
		color = map_info->assets[ld->tex_num][tex_y * IMG_SIZE + ld->tex_x];
		if (map_info->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		buff[ld->y][x] = color;
	}
	else
		buff[ld->y][x] = 0xFF00FF;
}

void	draw_line(t_map_info *map_info, int **buff, int x)
{
	t_line_data	ld;

	set_line_variables(&ld, map_info);
	ld.y = ld.draw_start;
	while (ld.y < ld.draw_end)
	{
		draw_pixel(map_info, buff, &ld, x);
		ld.y++;
	}
}
