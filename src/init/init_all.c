/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:25:44 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/04 15:32:00 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	*stock_tmp(t_map_info *map_info, char *path)
{
	t_img	tmp;
	int		*array;
	int		x;
	int		y;

	xpm_to_img(map_info, &tmp, path);
	array = ft_calloc(1, sizeof(int) * (IMG_SIZE * IMG_SIZE));
	if (!array)
		error_exit(map_info, "Failed to allocate memory for texture");
	y = -1;
	while (++y < IMG_SIZE)
	{
		x = -1;
		while (++x < IMG_SIZE)
			array[y * IMG_SIZE + x] = tmp.addr[y * (tmp.line_length / 4) + x];
	}
	mlx_destroy_image(map_info->mlx, tmp.img_mlx);
	return (array);
}

void	init_textures(t_map_info *map_info)
{
	map_info->assets = ft_calloc(5, sizeof(int *));
	if (!map_info->assets)
		error_exit(map_info, "Failed to allocate memory for textures array");
	printf("Loading textures...\n");	
	map_info->assets[NO] = stock_tmp(map_info, map_info->no_texture);
	map_info->assets[SO] = stock_tmp(map_info, map_info->so_texture);
	map_info->assets[WE] = stock_tmp(map_info, map_info->we_texture);
	map_info->assets[EA] = stock_tmp(map_info, map_info->ea_texture);
	printf("Textures loaded\n");
}

void	launch_game(t_map_info *map_info)
{
	map_info->img = malloc(sizeof(t_img));
	if (!map_info->img)
		error_exit(map_info, "Failed to allocate memory for image");

	set_img(map_info->img);
	init_mlx(map_info);
	map_pos(map_info);
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
	mlx_loop_hook(map_info->mlx, moves, map_info);
	mlx_loop(map_info->mlx);
}
