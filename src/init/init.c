/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:25:18 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/08 15:27:36 by ededemog         ###   ########.fr       */
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
		printf("Error:\n Failed to load textures: %s\n", tex);
		error_exit(map_info, "Texture loading failed");
	}
	img->addr = (int *)mlx_get_data_addr(img->img_mlx, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static void	init_plane(t_map_info *map_info, char c)
{
	if (c == 'S')
	{
		map_info->plane[0] = -0.66;
		map_info->plane[1] = 0;
	}
	if (c == 'N')
	{
		map_info->plane[0] = 0.66;
		map_info->plane[1] = 0;
	}
	if (c == 'E')
	{
		map_info->plane[0] = 0;
		map_info->plane[1] = 0.66;
	}
	if (c == 'W')
	{
		map_info->plane[0] = 0;
		map_info->plane[1] = -0.66;
	}
}

static void	init_spawn(int y, int x, char c, t_map_info *map_info)
{
	map_info->pos[0] = (double)x + 0.5;
	map_info->pos[1] = (double)y + 0.5;
	if (c == 'S')
	{
		map_info->dir[0] = 0;
		map_info->dir[1] = 1;
	}
	else if (c == 'N')
	{
		map_info->dir[0] = 0;
		map_info->dir[1] = -1;
	}
	else if (c == 'E')
	{
		map_info->dir[0] = 1;
		map_info->dir[1] = 0;
	}
	else if (c == 'W')
	{
		map_info->dir[0] = -1;
		map_info->dir[1] = 0;
	}
	init_plane(map_info, c);
}

void	map_pos(t_map_info *map_info)
{
	int	i;
	int	j;

	i = -1;
	while (map_info->map[++i])
	{
		j = -1;
		while (map_info->map[i][++j])
		{
			if (map_info->map[i][j] == 'N' || map_info->map[i][j] == 'S'
				|| map_info->map[i][j] == 'E' || map_info->map[i][j] == 'W')
				init_spawn(i, j, map_info->map[i][j], map_info);
		}
	}
}
