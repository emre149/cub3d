/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:20 by ededemog          #+#    #+#             */
/*   Updated: 2025/04/02 10:20:40 by ededemog         ###   ########.fr       */
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

static void	init_map_info_pointers(t_map_info *map_info)
{
	map_info->no_texture = NULL;
	map_info->so_texture = NULL;
	map_info->we_texture = NULL;
	map_info->ea_texture = NULL;
	map_info->sprite = NULL;
	map_info->door_text = NULL;
	map_info->map = NULL;
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
	if (map_info->door_text)
		free(map_info->door_text);
	if (error_msg)
		printf("%s", error_msg);
	exit(1);
}

int	main(int ac, char **av)
{
	t_map_info	map_info;

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
	init_map_info_pointers(&map_info);
	if (!read_map_file(&map_info, av[1]))
		free_and_exit(&map_info, "Error: Failed to read map file\n");
	if (!parse_config(&map_info))
		free_and_exit(&map_info, "Error: Failed to parse map file\n");
	launch_game(&map_info);
	return (0);
}

int	render_frame(void *param)
{
	t_map_info	*map_info;

	map_info = (t_map_info *)param;
	if (moves(map_info))
		raycasting(map_info);
	return (0);
}
