/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:12:14 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/21 17:47:11 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	apply_ceiling_color(t_map_info *map_info, t_img *img, int index)
{
	img->addr[index] = map_info->ceiling_color;
}

static void	apply_floor_color(t_map_info *map_info, t_img *img, int index)
{
	img->addr[index] = map_info->floor_color;
}

static void	process_pixel(t_map_info *map_info, t_img *img, int **buff,
		t_pixel_data *pd)
{
	int	index;

	index = pd->i * (img->line_length / 4) + pd->x;
	if (buff[pd->i][pd->x] > 0)
	{
		img->addr[index] = buff[pd->i][pd->x];
		pd->has_texture = 1;
	}
	else if (pd->i < SCREEN_HEIGHT / 2)
		apply_ceiling_color(map_info, img, index);
	else
		apply_floor_color(map_info, img, index);
}

static void	process_image_row(t_map_info *map_info, t_img *img, int **buff,
		t_pixel_data *pd)
{
	pd->x = -1;
	while (++(pd->x) < SCREEN_WIDTH)
		process_pixel(map_info, img, buff, pd);
}

void	add_img(t_map_info *map_info, int **buff, t_img *img)
{
	t_pixel_data	pd;

	pd.has_texture = 0;
	ft_bzero(img, sizeof(t_img));
	img->img_mlx = mlx_new_image(map_info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = (int *)mlx_get_data_addr(img->img_mlx, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	pd.i = -1;
	while (++(pd.i) < SCREEN_HEIGHT)
		process_image_row(map_info, img, buff, &pd);
	mlx_put_image_to_window(map_info->mlx, map_info->win, img->img_mlx, 0, 0);
	mlx_destroy_image(map_info->mlx, img->img_mlx);
}
