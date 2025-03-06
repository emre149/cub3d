/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:59 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/06 17:00:59 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	draw_line(t_map_info *map_info, int **buff, int x)
{
	if (map_info->side == 0)
		map_info->wall_x = map_info->pos[Y] + map_info->wall_dist
			* map_info->ray_dir[Y];
	else
		map_info->wall_x = map_info->pos[X] + map_info->wall_dist
			* map_info->ray_dir[X];
	map_info->wall_x -= floor(map_info->wall_x);
	map_info->tex[X] = (int)(map_info->wall_x * (double)IMG_SIZE);
	if ((map_info->side == 0 && map_info->ray_dir[X] > 0)
		|| (map_info->side == 1 && map_info->ray_dir[Y] < 0))
		map_info->tex[X] = IMG_SIZE - map_info->tex[X] - 1;
	map_info->tex_step = 1.0 * IMG_SIZE / map_info->line_height;
	map_info->tex_pos = (map_info->draw_start - SCREEN_HEIGHT / 2
			+ map_info->line_height / 2) * map_info->tex_step;
	map_info->y = map_info->draw_start;
	while (map_info->y < map_info->draw_end)
	{
		map_info->tex[Y] = (int)map_info->tex_pos & (IMG_SIZE - 1);
		map_info->tex_pos += map_info->tex_step;
		map_info->color = map_info->assets[map_info->tex_num][IMG_SIZE
			* map_info->tex[Y] + map_info->tex[X]];
		buff[map_info->y][x] = map_info->color;
		map_info->y++;
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

void test_single_texture(t_map_info *map_info, int texture_id)
{
    t_img img;
    int x, y;
    int width, height;
    
    // Vérifier si la texture existe
    if (!map_info->assets[texture_id]) {
        printf("Texture %d n'est pas chargée\n", texture_id);
        return;
    }
    
    // Récupérer les dimensions de la texture
    width = IMG_SIZE;
    height = IMG_SIZE;
    
    printf("Affichage de la texture %d: largeur=%d, hauteur=%d\n", 
           texture_id, width, height);
    
    // Créer une nouvelle image
    ft_bzero(&img, sizeof(t_img));
    img.img_mlx = mlx_new_image(map_info->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    img.addr = (int *)mlx_get_data_addr(img.img_mlx, &img.bits_per_pixel, 
                                        &img.line_length, &img.endian);
    
    // Remplir l'écran avec la texture répétée
    for (y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            // Calculer les coordonnées de texture (répétition)
            int tex_x = x % width;
            int tex_y = y % height;
            
            // Calculer l'index dans le tableau de texture
            int tex_index = tex_y * width + tex_x;
            
            // Vérifier que l'index est valide
            if (tex_index >= 0 && tex_index < width * height) {
                // Récupérer la couleur et l'appliquer
                int color = map_info->assets[texture_id][tex_index];
                img.addr[y * (img.line_length / 4) + x] = color;
            } else {
                // Couleur d'erreur
                img.addr[y * (img.line_length / 4) + x] = 0xFF00FF; // Rose
            }
        }
    }
    
    // Afficher l'image
    mlx_put_image_to_window(map_info->mlx, map_info->win, img.img_mlx, 0, 0);
    mlx_destroy_image(map_info->mlx, img.img_mlx);
}
