/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:21:17 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/08 15:57:51 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_hook(int keycode, t_map_info *map_info)
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
		map_info->rot_left = -1;
	if (keycode == XK_Right)
		map_info->rot_right = 1;
	if (keycode == XK_e)
		interact_with_door(map_info);
	return (0);
}

int	key_release(int keycode, t_map_info *map_info)
{
	if (keycode == XK_w && map_info->move[Y] == 1)
		map_info->move[Y] = 0;
	if (keycode == XK_s && map_info->move[Y] == -1)
		map_info->move[Y] = 0;
	if (keycode == XK_a && map_info->move[X] == -1)
		map_info->move[X] = 0;
	if (keycode == XK_d && map_info->move[X] == 1)
		map_info->move[X] = 0;
	if (keycode == XK_Left && map_info->rot_left == -1)
		map_info->rot_left = 0;
	if (keycode == XK_Right && map_info->rot_right == 1)
		map_info->rot_right = 0;
	return (0);
}
