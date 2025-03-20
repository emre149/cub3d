/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:25:44 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/20 21:01:54 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	launch_game(t_map_info *map_info)
{
	map_info->img = malloc(sizeof(t_img));
	if (!map_info->img)
		error_exit(map_info, "Failed to allocate memory for image");
	set_img(map_info->img);
	init_mlx(map_info);
	map_pos(map_info);
	init_doors(map_info);
	init_mouse_controls(map_info);
	init_textures(map_info);
	map_info->move[X] = 0;
	map_info->move[Y] = 0;
	map_info->moved = 0;
	map_info->rot_left = 0;
	map_info->rot_right = 0;
	raycasting(map_info);
	mlx_hook(map_info->win, KeyPress, KeyPressMask, key_hook, map_info);
	mlx_hook(map_info->win, KeyRelease, KeyReleaseMask, key_release, map_info);
	mlx_hook(map_info->win, DestroyNotify, StructureNotifyMask, destroy_game,
		map_info);
	mlx_hook(map_info->win, MotionNotify, PointerMotionMask, handle_mouse_move,
		map_info);
	mlx_loop_hook(map_info->mlx, render_frame, map_info);
	mlx_loop(map_info->mlx);
}

void	set_img(t_img *img)
{
	img->img_mlx = NULL;
	img->addr = NULL;
	img->line_length = 0;
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	update_camera_bob(t_map_info *map_info)
{
	struct timeval			current_time;
	static struct timeval	last_time;
	double					delta_time;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0 && last_time.tv_usec == 0)
		last_time = current_time;
	delta_time = (current_time.tv_sec - last_time.tv_sec)
		+ (current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	if (delta_time > 0.1)
		delta_time = 0.1;
	last_time = current_time;
	map_info->time_counter += delta_time * map_info->bob_speed;
	if (map_info->is_walking)
	{
		map_info->bob_height = sin(map_info->time_counter)
			* map_info->bob_amplitude;
	}
	else
	{
		if (fabs(map_info->bob_height) > 0.1)
			map_info->bob_height *= 0.8;
		else
			map_info->bob_height = 0;
	}
}

void	init_camera_bob(t_map_info *map_info)
{
	map_info->bob_height = 0.0;
	map_info->bob_speed = 5.0;
	map_info->bob_amplitude = 5.0;
	map_info->is_walking = 0;
	map_info->time_counter = 0.0;
}
