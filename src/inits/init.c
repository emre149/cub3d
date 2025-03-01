/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:05:56 by marvin            #+#    #+#             */
/*   Updated: 2025/02/24 03:05:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

static void init_dir(t_map_info *map_info, char who)
{
    if (who == 'N')
    {
        map_info->dir_x = -1;
        map_info->dir_y = 0;
    }
    else if (who == 'S')
    {
        map_info->dir_x = 1;
        map_info->dir_y = 0;
    }
    else if (who == 'E')
    {
        map_info->dir_x = 0;
        map_info->dir_y = 1;
    }
    else if (who == 'W')
    {
        map_info->dir_x = 0;
        map_info->dir_y = -1;
    }
    map_info->plane_x = map_info->dir_y * (-1) * 0.66;
    map_info->plane_y = map_info->dir_x * 0.66;
}

void map_pos(t_map_info *map_info)
{
    int i;
    int j;

    i = -1;
    while (map_info->map[++i])
    {
        j = -1;
        while (map_info->map[i][++j])
        {
            if (map_info->map[i][j] == 'N' || map_info->map[i][j] == 'S' ||
                map_info->map[i][j] == 'E' || map_info->map[i][j] == 'W')
            {
                map_info->player_x = j;
                map_info->player_y = i;
                map_info->player_dir = map_info->map[i][j];
                init_dir(map_info, map_info->player_dir);
            }
        }
    }
}

void init_mlx(t_map_info *map_info)
{
    map_info->mlx = mlx_init();
    if (!map_info->mlx)
        error_exit(map_info, "Failed to initialize mlx");
    map_info->win = mlx_new_window(map_info->mlx, map_info->map_width, map_info->map_height, "Cub3D");
    if (!map_info->win)
        error_exit(map_info, "Failed to create window");
}

void xpm_to_img(t_map_info *map_info, t_img *img, char *tex)
{
    set_img(img);
    img->img_mlx = mlx_xpm_file_to_image(map_info->mlx, tex, &img->width, &img->height);
    if (!map_info->img->img_mlx)
        error_exit(map_info, "Failed to load no texture");
    img->addr = (int *)mlx_get_data_addr(img->img_mlx, &img->bits_per_pixel, &img->line_length, &img->endian);
}

