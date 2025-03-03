/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:25:18 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/03 16:29:03 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	init_mlx(t_map_info *map_info)
{
	map_info->mlx = mlx_init();
	if (!map_info->mlx)
		error_exit(map_info, "Failed to initialize mlx");
	map_info->win = mlx_new_window(map_info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	if (!map_info->win)
	{
		free(map_info->mlx);
		error_exit(map_info, "Failed to create window");
	}
}

void	xpm_to_img(t_map_info *map_info, t_img *img, char *tex)
{
	set_img(img);
	img->img_mlx = mlx_xpm_file_to_image(map_info->mlx, tex, &img->width,
			&img->height);
	if (!img->img_mlx)
	{
		write(2, "Failed to load texture: ", 24);
		write(2, tex, ft_strlen(tex));
		write(2, "\n", 1);
		error_exit(map_info, "Texture loading failed");
	}
	img->addr = (int *)mlx_get_data_addr(img->img_mlx, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	map_pos(t_map_info *map_info)
{
	map_info->pos[X] = (double)map_info->player_x / 10;
	map_info->pos[Y] = (double)map_info->player_y / 10;

	if (map_info->player_dir == 'N')
	{
		map_info->dir[X] = 0;
		map_info->dir[Y] = -1;
		map_info->plane[X] = 0.66;
		map_info->plane[Y] = 0;
	}
	else if (map_info->player_dir == 'S')
	{
		map_info->dir[X] = 0;
		map_info->dir[Y] = 1;
		map_info->plane[X] = -0.66;
		map_info->plane[Y] = 0;
	}
	else if (map_info->player_dir == 'E')
	{
		map_info->dir[X] = 1;
		map_info->dir[Y] = 0;
		map_info->plane[X] = 0;
		map_info->plane[Y] = 0.66;
	}
	else if (map_info->player_dir == 'W')
	{
		map_info->dir[X] = -1;
		map_info->dir[Y] = 0;
		map_info->plane[X] = 0;
		map_info->plane[Y] = -0.66;
	}

	map_info->dir_x = map_info->dir[X];
	map_info->dir_y = map_info->dir[Y];
	map_info->plane_x = map_info->plane[X];
	map_info->plane_y = map_info->plane[Y];
}
