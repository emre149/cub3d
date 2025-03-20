/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:00:32 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/20 15:08:05 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	update_direction_vectors(t_map_info *data, double rotation_amount)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	data->dir_x = data->dir_x * cos(rotation_amount) - data->dir_y
		* sin(rotation_amount);
	data->dir_y = old_dir_x * sin(rotation_amount) + data->dir_y
		* cos(rotation_amount);
	data->plane_x = data->plane_x * cos(rotation_amount) - data->plane_y
		* sin(rotation_amount);
	data->plane_y = old_plane_x * sin(rotation_amount) + data->plane_y
		* cos(rotation_amount);
	data->dir[X] = data->dir_x;
	data->dir[Y] = data->dir_y;
	data->plane[X] = data->plane_x;
	data->plane[Y] = data->plane_y;
	data->moved = 1;
}

static int	process_mouse_rotation(t_map_info *data, int x)
{
	int		delta_x;
	double	rotation_amount;

	delta_x = x - data->mouse.prev_x;
	if (delta_x != 0)
	{
		rotation_amount = delta_x * data->rot_speed;
		update_direction_vectors(data, rotation_amount);
		return (1);
	}
	return (0);
}

static void	recenter_mouse_if_needed(t_map_info *data, int x)
{
	int	win_width;
	int	win_height;

	mlx_get_screen_size(data->mlx, &win_width, &win_height);
	if (abs(x - win_width / 2) > 10)
	{
		mlx_mouse_move(data->mlx, data->win, win_width / 2, win_height / 2);
		data->mouse.prev_x = win_width / 2;
	}
	else
		data->mouse.prev_x = x;
}

int	handle_mouse_move(int x, int y, void *param)
{
	t_map_info	*data;

	data = (t_map_info *)param;
	data->mouse.x = x;
	data->mouse.y = y;
	if (!data->mouse.is_captured)
		return (0);
	process_mouse_rotation(data, x);
	recenter_mouse_if_needed(data, x);
	return (0);
}

void	init_mouse_controls(t_map_info *data)
{
	int	win_width;
	int	win_height;

	mlx_get_screen_size(data->mlx, &win_width, &win_height);
	data->mouse.prev_x = win_width / 2;
	data->mouse.x = win_width / 2;
	data->mouse.y = win_height / 2;
	data->mouse.is_captured = 0;
	data->rot_speed = 0.002;
	printf("Mouse controls initialized. Press 'm' to toggle mouse capture.\n");
}
