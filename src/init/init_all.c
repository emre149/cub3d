/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:25:44 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/13 17:24:30 by ededemog         ###   ########.fr       */
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
	int	has_doors;
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	map_info->assets = ft_calloc(6, sizeof(int *));
	if (!map_info->assets)
		error_exit(map_info, "Failed to allocate memory for textures array");
	printf("Loading textures...\n");
	map_info->assets[NO] = stock_tmp(map_info, map_info->no_texture);
	map_info->assets[SO] = stock_tmp(map_info, map_info->so_texture);
	map_info->assets[WE] = stock_tmp(map_info, map_info->we_texture);
	map_info->assets[EA] = stock_tmp(map_info, map_info->ea_texture);
	has_doors = 0;
	i = 0;
	j = 0;
	while (map_info->map[i])
	{
		j = 0;
		while (map_info->map[i][j])
		{
			if (map_info->map[i][j] == DOOR_CLOSE
				|| map_info->map[i][j] == DOOR_OPEN)
			{
				has_doors = 1;
				break ;
			}
			j++;
		}
		if (has_doors)
			break ;
		i++;
	}
	if (has_doors && !map_info->door_text)
		error_exit(map_info,
			"Des portes sont présentes dans la carte mais aucune texture de porte (DO) n'est définie");
	if (!has_doors && map_info->door_text)
		error_exit(map_info,
			"Une texture de porte (DO) est définie mais aucune porte n'est présente dans la carte");
	if (map_info->door_text)
		map_info->assets[DOOR] = stock_tmp(map_info, map_info->door_text);
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

	init_doors(map_info);
	init_mouse_controls(map_info);
	init_textures(map_info);
	map_info->move[X] = 0;
	map_info->move[Y] = 0;
	map_info->moved = 0;
	map_info->rot_left = 0;
	map_info->rot_right = 0;
	raycasting(map_info);
// In launch_game function
	mlx_hook(map_info->win, KeyPress, KeyPressMask, key_hook, map_info);
	mlx_hook(map_info->win, KeyRelease, KeyReleaseMask, key_release, map_info);
	mlx_hook(map_info->win, DestroyNotify, StructureNotifyMask, destroy_game, map_info);
	mlx_hook(map_info->win, MotionNotify, PointerMotionMask, handle_mouse_move, map_info);	
	mlx_loop_hook(map_info->mlx, render_frame, map_info);
	mlx_loop(map_info->mlx);
}
