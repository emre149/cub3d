/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:08:05 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 14:08:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int *stock_tmp(t_map_info *map_info, char *line)
{
    t_img   tmp;
    int     *array;
    int     x;
    int     y;

    xpm_to_img(map_info, &tmp, line);
    array = ft_calloc(1, sizeof(int) * (IMG_SIZE * IMG_SIZE));
    if (!array)
        error_exit(map_info, "Failed to allocate memory");
    y = -1;
    while (++y < IMG_SIZE)
    {
        x = -1;
        while (++x < IMG_SIZE)
            array[y * IMG_SIZE + x] = tmp.addr[y * IMG_SIZE + x];
    }
    mlx_destroy_image(map_info->mlx, tmp.img_mlx);
    return (array);
}

void init_textures(t_map_info *map_info)
{
    map_info->text = ft_calloc(5, sizeof(int *));
    if (!map_info->text)
        error_exit(map_info, "Failed to allocate memory for textures");
    map_info->text[NO] = stock_tmp(map_info, map_info->no_texture);
    map_info->text[SO] = stock_tmp(map_info, map_info->so_texture);
    map_info->text[WE] = stock_tmp(map_info, map_info->we_texture);
    map_info->text[EA] = stock_tmp(map_info, map_info->ea_texture);
}

void launch_game(t_map_info *map_info)
{
    init_mlx(map_info);
    map_pos(map_info);
    init_textures(map_info);
    raycasting(map_info);
    mlx_hook(map_info->win, KeyPress, KeyPressMask, key_hook, map_info);
    mlx_hook(map_info->win, KeyRelease, KeyReleaseMask, key_release, map_info);
    mlx_hook(map_info->win, DestroyNotify, 0, destroy_game, map_info);
    mlx_loop_hook(map_info->mlx, moves, map_info);
    mlx_loop(map_info->mlx);
}
