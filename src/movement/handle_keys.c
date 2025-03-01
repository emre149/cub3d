/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:03:49 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 16:39:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int destroy_game(t_map_info *map_info)
{
	free_all(map_info);
    printf("Game destroyed\n");
	exit(0);
    return (0);
}

int key_hook(int keycode, t_map_info *map_info)
{
    if (keycode == ESC)
        destroy_game(map_info);
    if (keycode == XK_w)
        map_info->move[Y] = 1;
    if (keycode == XK_s)
        map_info->move[Y] = -1;
    if (keycode == XK_a)
        map_info->move[X] = -1;
    if (keycode == XK_d)
        map_info->move[X] = 1;
    if (keycode == XK_Left)
        map_info->rot_left -= 1;
    if (keycode == XK_Right)
        map_info->rot_right += 1;
    return (0);
}

int key_release(int keycode, t_map_info *map_info)
{
    if (keycode == XK_w && map_info->move[Y] == 1)
        map_info->move[Y] = 0;
    if (keycode == XK_s && map_info->move[Y] == -1)
        map_info->move[Y] = 0;
    if (keycode == XK_a && map_info->move[X] == -1)
        map_info->move[X] = 0;
    if (keycode == XK_d && map_info->move[X] == 1)
        map_info->move[X] = 0;
    if (keycode == XK_Left && map_info->rot_left <= -1)
        map_info->rot_left = 0;
    if (keycode == XK_Right && map_info->rot_right >= 1)
        map_info->rot_right = 0;
    return (0);
}
