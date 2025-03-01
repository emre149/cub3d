/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:20 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/28 12:10:43 by ededemog         ###   ########.fr       */
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

static void	free_and_exit(t_map_info *map_info, char *error_msg)
{
	if (map_info->map)
		free_map(map_info->map);
	if (map_info->no_texture)
		free(map_info->no_texture);
	if (map_info->so_texture)
		free(map_info->so_texture);
	if (map_info->we_texture)
		free(map_info->we_texture);
	if (map_info->ea_texture)
		free(map_info->ea_texture);
	if (map_info->sprite)
		free(map_info->sprite);
	if (error_msg)
		write(2, error_msg, ft_strlen(error_msg));
	exit(1);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map_info	map_info;

	if (ac != 2)
	{
		write(2, "Usage: ./cub3D <map.cub>\n", 25);
		return (1);
	}
	if (!is_valid_map_file(av[1]))
	{
		write(2, "Error: Invalid file extension. Use .cub\n", 40);
		return (1);
	}
	ft_memset(&map_info, 0, sizeof(t_map_info));
	if (!read_map_file(&map_info, av[1]))
		free_and_exit(&map_info, "Error: Failed to read map file\n");
	if (!parse_config(&map_info))
		free_and_exit(&map_info, "Error: Failed to parse map file\n");
	data.mlx = mlx_init();
	if (!data.mlx)
		free_and_exit(&map_info, "Error: Failed to initialize MLX\n");
	data.win = mlx_new_window(data.mlx, map_info.map_width, map_info.map_height,
			"Cub3D");
	if (!data.win)
	{
		free(data.mlx);
		free_and_exit(&map_info, "Error: Failed to create window\n");
	}
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, key_hook, &data);
	render_map(&data, &map_info);
	mlx_loop(data.mlx);
	return (0);
}
