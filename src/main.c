/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:20 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/08 16:05:21 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_window(t_map_info *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
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
		printf("%s", error_msg);
	exit(1);
}

int	main(int ac, char **av)
{
	t_map_info	map_info;

	map_info.no_texture = NULL;
	map_info.so_texture = NULL;
	map_info.we_texture = NULL;
	map_info.ea_texture = NULL;
	map_info.sprite = NULL;
	map_info.door_text = NULL;
	if (ac != 2)
	{
		printf("Error:\n Usage: ./cub3d map_file.cub\n");
		return (1);
	}
	if (!is_valid_map_file(av[1]))
	{
		printf("Error:\n Invalid map file\n");
		return (1);
	}
	ft_memset(&map_info, 0, sizeof(t_map_info));
	if (!read_map_file(&map_info, av[1]))
		free_and_exit(&map_info, "Error: Failed to read map file\n");
	if (!parse_config(&map_info))
		free_and_exit(&map_info, "Error: Failed to parse map file\n");
	launch_game(&map_info);
	return (0);
}
