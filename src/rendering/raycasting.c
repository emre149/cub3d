/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:59 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/08 16:42:50 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_line(t_map_info *map_info, int **buff, int x)
{
	int y;
	int color;
	double wall_x;
	int tex_x;
	int tex_y;
	
	int draw_start = map_info->draw_start;
	int draw_end = map_info->draw_end;
	
	int tex_num = map_info->tex_num;
	
	if (map_info->side == 0)
		wall_x = map_info->pos[1] + map_info->wall_dist * map_info->ray_dir[1];
	else
		wall_x = map_info->pos[0] + map_info->wall_dist * map_info->ray_dir[0];
	wall_x -= floor(wall_x);
	
	tex_x = (int)(wall_x * (double)IMG_SIZE);
	if ((map_info->side == 0 && map_info->ray_dir[0] > 0) || 
		(map_info->side == 1 && map_info->ray_dir[1] < 0))
		tex_x = IMG_SIZE - tex_x - 1;
	
	double step = 1.0 * IMG_SIZE / map_info->line_height;
	double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + map_info->line_height / 2) * step;
	
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (IMG_SIZE - 1);
		tex_pos += step;
		
		if (map_info->assets[tex_num] != NULL)
		{
			color = map_info->assets[tex_num][tex_y * IMG_SIZE + tex_x];
			
			if (map_info->side == 1)
				color = (color >> 1) & 0x7F7F7F;
			
			buff[y][x] = color;
		}
		else
		{
			buff[y][x] = 0xFF00FF;
		}
		y++;
	}
} 

static void	clean_buff(int **buff)
{
	int	i;

	i = -1;
	while (++i < SCREEN_HEIGHT)
		free(buff[i]);
	free(buff);
}

static void	add_img(t_map_info *map_info, int **buff, t_img *img)
{
	int	x;
	int	index;
	int	i;

	ft_bzero(img, sizeof(t_img));
	img->img_mlx = mlx_new_image(map_info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = (int *)mlx_get_data_addr(img->img_mlx, &img->bits_per_pixel,
			&img->line_length, &img->endian);
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
