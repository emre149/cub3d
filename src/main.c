/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:22:20 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/27 17:24:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void ft_init(t_map_info *map_info)
{
	map_info->no_texture = NULL;
	map_info->so_texture = NULL;
	map_info->we_texture = NULL;
	map_info->ea_texture = NULL;
	map_info->map = NULL;
	map_info->map_height = 0;
	map_info->map_width = 0;
	map_info->mlx = NULL;
	map_info->win = NULL;
	map_info->img = NULL;
	map_info->text = NULL;
	map_info->floor_color = 0;
	map_info->ceiling_color = 0;
	map_info->moved = 0;
	map_info->rot_left = 0;
	map_info->rot_right = 0;
	map_info->move[0] = 0;
	map_info->move[1] = 0;
	map_info->player_dir = 0;
	map_info->player_x = 0;
	map_info->player_y = 0;
	
}
int main(int argc, char **argv)
{
	t_map_info map_info;

	ft_init(&map_info);
	if (argc != 2)
		error_exit(&map_info, "Usage: ./cub3d <map_file>");
	
	printf("Checking map file...\n");
	if (!is_valid_map_file(argv[1]))
		error_exit(&map_info, "Invalid map file");
	
	printf("Reading map file...\n");
	if (!read_map_file(&map_info, argv[1]))
		error_exit(&map_info, "Failed to read map file");
	
	printf("Parsing config...\n");
	if (!parse_config(&map_info))
		error_exit(&map_info, "Failed to parse config");
	
	printf("Detecting player...\n");
	detect_player(&map_info);
	
	printf("Launching game...\n");
	launch_game(&map_info);
	return (0);
}