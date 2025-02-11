/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:20 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/11 19:35:07 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map_info	map_info;
	int			debug_i;

	if (ac != 2)
	{
		write(2, "Error:\nUsage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	if (!is_valid_map_file(av[1]))
	{
		write(2, "Error: Invalid file extension. Use .cub\n", 40);
		return (1);
	}
	ft_memset(&map_info, 0, sizeof(t_map_info));
	if (!read_map_file(&map_info, av[1]) || !parse_config(&map_info))
	{
		write(2, "Error: Failed to parse map file\n", 32);
		return (1);
	}
	printf("Resolution: %d x %d\n", map_info.map_width, map_info.map_height);
	printf("Textures: NO=%s, SO=%s, WE=%s, EA=%s, S=%s\n", map_info.no_texture,
		map_info.so_texture, map_info.we_texture, map_info.ea_texture,
		map_info.sprite);
	printf("Floor color: %d\n", map_info.floor_color);
	printf("Ceiling color: %d\n", map_info.ceiling_color);
	debug_i = 0;
	while (map_info.map[debug_i])
	{
		printf("Line %d: %s\n", debug_i, map_info.map[debug_i]);
		debug_i++;
	}
	printf("Total map lines: %d\n", debug_i);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 800, 600, "Cub3D");
	if (!data.win)
	{
		free(data.mlx);
		return (1);
	}
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
