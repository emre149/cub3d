/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:25:44 by ededemog          #+#    #+#             */
/*   Updated: 2025/04/02 10:20:26 by ededemog         ###   ########.fr       */
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
