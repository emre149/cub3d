/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:20 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/07 16:47:23 by ededemog         ###   ########.fr       */
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

	data.mlx = mlx_init();
	if (!data.mlx)
	{
		free_map_info(&map_info);
		return (1);
	}

	data.win = mlx_new_window(data.mlx, 800, 600, "Cub4d");
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
}

