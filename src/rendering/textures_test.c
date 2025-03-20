/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 21:13:16 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/20 21:14:12 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_texture_loaded(t_map_info *map_info, int texture_id)
{
	if (!map_info->assets[texture_id])
	{
		printf("Texture %d n'est pas chargée\n", texture_id);
		return ;
	}
}

static void	init_texture_test_img(t_map_info *map_info, t_img *img)
{
	ft_bzero(img, sizeof(t_img));
	img->img_mlx = mlx_new_image(map_info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img->addr = (int *)mlx_get_data_addr(img->img_mlx, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static int	get_texture_color(t_map_info *map_info, int texture_id,
		int tex_index)
{
	int	color;

	if (tex_index >= 0 && tex_index < IMG_SIZE * IMG_SIZE)
		color = map_info->assets[texture_id][tex_index];
	else
		color = 0xFF00FF;
	return (color);
}

static void	draw_texture_row(t_map_info *map_info, t_img *img,
		t_texture_test *tt)
{
	int	x;
	int	tex_x;
	int	tex_index;
	int	color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		tex_x = x % tt->width;
		tex_index = tt->tex_y * tt->width + tex_x;
		color = get_texture_color(map_info, tt->texture_id, tex_index);
		img->addr[tt->y * (img->line_length / 4) + x] = color;
		x++;
	}
}

void	test_single_texture(t_map_info *map_info, int texture_id)
{
	t_img			img;
	t_texture_test	tt;

	check_texture_loaded(map_info, texture_id);
	tt.width = IMG_SIZE;
	tt.height = IMG_SIZE;
	tt.texture_id = texture_id;
	printf("Affichage de la texture %d: largeur=%d, hauteur=%d\n", texture_id,
		tt.width, tt.height);
	init_texture_test_img(map_info, &img);
	tt.y = 0;
	while (tt.y < SCREEN_HEIGHT)
	{
		tt.tex_y = tt.y % tt.height;
		draw_texture_row(map_info, &img, &tt);
		tt.y++;
	}
	mlx_put_image_to_window(map_info->mlx, map_info->win, img.img_mlx, 0, 0);
	mlx_destroy_image(map_info->mlx, img.img_mlx);
}
