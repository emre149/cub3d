/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:36:52 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/20 21:15:07 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	destroy_game(t_map_info *map_info)
{
	free_all(map_info);
	printf("Game succesfully destroyed\n");
	exit(0);
	return (0);
}

void	interact_with_door(t_map_info *map_info)
{
	int	target_x;
	int	target_y;

	target_x = (int)(map_info->pos[X] + map_info->dir[X]);
	target_y = (int)(map_info->pos[Y] + map_info->dir[Y]);
	if (is_door(map_info, target_x, target_y))
	{
		toggle_door(map_info, target_x, target_y);
	}
	else
	{
		printf("No door to interact with\n");
	}
}

static void	handle_mouse_capture_state(t_map_info *data, int win_width,
		int win_height)
{
	if (data->mouse.is_captured)
	{
		mlx_mouse_move(data->mlx, data->win, win_width / 2, win_height / 2);
		data->mouse.prev_x = win_width / 2;
	}
	else
	{
		mlx_mouse_show(data->mlx, data->win);
	}
}

int	toggle_mouse_capture(int keycode, void *param)
{
	t_map_info	*data;
	int			win_width;
	int			win_height;
	char		*status;

	data = (t_map_info *)param;
	if (keycode != 109)
		return (0);
	data->mouse.is_captured = !data->mouse.is_captured;
	if (data->mouse.is_captured)
		status = "ON";
	else
		status = "OFF";
	printf("Mouse capture toggled: %s (keycode: %d)\n", status, keycode);
	mlx_get_screen_size(data->mlx, &win_width, &win_height);
	handle_mouse_capture_state(data, win_width, win_height);
	return (0);
}

void	clean_buff(int **buff)
{
	int	i;

	i = -1;
	while (++i < SCREEN_HEIGHT)
		free(buff[i]);
	free(buff);
}
