/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:13:04 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 16:13:26 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	clean_buff(int **buff)
{
	int	i;

	i = -1;
	while (++i < SCREEN_HEIGHT)
		free(buff[i]);
	free(buff);
}

static void	set_pixel_color(t_map_info *map_info, t_img *img, int **buff,
		int index)
{
	int	i;
	int	x;

	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			index = i * (img->line_length / 4) + x;
			if (buff[i][x] > 0)
				img->addr[index] = buff[i][x];
			else if (i < SCREEN_HEIGHT / 2)
				img->addr[index] = map_info->ceiling_color;
			else
				img->addr[index] = map_info->floor_color;
		}
	}
}

static void	add_img(t_map_info *map_info, int **buff, t_img *img)
{
	int	index;

	ft_bzero(img, sizeof(t_img));
	img->img_mlx = mlx_new_image(map_info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = (int *)mlx_get_data_addr(img->img_mlx, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	index = 0;
	set_pixel_color(map_info, img, buff, index);
	mlx_put_image_to_window(map_info->mlx, map_info->win, img->img_mlx, 0, 0);
	mlx_destroy_image(map_info->mlx, img->img_mlx);
}

void	raycasting(t_map_info *map_info)
{
	int		**buff;
	int		i;
	t_img	img;

	buff = init_buff(map_info);
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		init_ray(map_info, i);
		step_sidedist(map_info);
		algo_dda(map_info);
		calc_dist(map_info);
		draw_line(map_info, buff, i);
		i++;
	}
	add_img(map_info, buff, &img);
	clean_buff(buff);
	draw_mini_map(map_info, map_info);
}
