/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:20 by ededemog          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/11 15:20:04 by ededemog         ###   ########.fr       */
=======
/*   Updated: 2025/02/07 16:47:23 by ededemog         ###   ########.fr       */
>>>>>>> 1846e4ad457c65975e64a6830ee988060fee7323
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
<<<<<<< HEAD
	t_data data;
	t_map_info map_info;

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

	// Debug: afficher les informations du fichier parsé
	printf("Resolution: %d x %d\n", map_info.map_width, map_info.map_height);
	printf("Textures: NO=%s, SO=%s, WE=%s, EA=%s, S=%s\n", map_info.no_texture,
		map_info.so_texture, map_info.we_texture, map_info.ea_texture,
		map_info.sprite);
	printf("Floor color: %d\n", map_info.floor_color);
	printf("Ceiling color: %d\n", map_info.ceiling_color);
=======
	t_data	data;
	t_map_info	map_info;

	if (ac != 2)
	{
		write(1, "Error:\nUsage: <map.cub>\n", 24);
		return (1);
	}
	if (!parse_map_file(&map_info, av[1]))
	{
		write(1, "Error:\nFailed to parse map file\n", 32);
		free_map_info(&map_info);
		return (1);
	}
>>>>>>> 1846e4ad457c65975e64a6830ee988060fee7323

	data.mlx = mlx_init();
	if (!data.mlx)
	{
		free_map_info(&map_info);
		return (1);
<<<<<<< HEAD

	data.win = mlx_new_window(data.mlx, 800, 600, "Cub3D");
=======
	}

	data.win = mlx_new_window(data.mlx, 800, 600, "Cub4d");
>>>>>>> 1846e4ad457c65975e64a6830ee988060fee7323
	if (!data.win)
	{
		free_map_info(&map_info);
		free(data.mlx);
		return (1);
	}

	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, key_hook, &data);

	mlx_loop(data.mlx);
	return (0);
<<<<<<< HEAD
}
=======
}

>>>>>>> 1846e4ad457c65975e64a6830ee988060fee7323
