/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:00:32 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/13 18:40:36 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int handle_mouse_move(int x, int y, void *param)
{
    t_map_info *data = (t_map_info *)param;
    int win_width, win_height;
    
    // Store current position
    data->mouse.x = x;
    data->mouse.y = y;

    // Only handle movement if mouse is captured
    if (!data->mouse.is_captured)
        return (0);
        
    mlx_get_screen_size(data->mlx, &win_width, &win_height);
    
    // Calculate delta from previous position
    int delta_x = x - data->mouse.prev_x;
    
    if (delta_x != 0)
    {
        // Use smaller rotation amount
        double rotation_amount = delta_x * data->rot_speed;
        double old_dir_x = data->dir_x;
        double old_plane_x = data->plane_x;
        
        // Rotate view direction
        data->dir_x = data->dir_x * cos(rotation_amount) - data->dir_y * sin(rotation_amount);
        data->dir_y = old_dir_x * sin(rotation_amount) + data->dir_y * cos(rotation_amount);
        
        // Rotate camera plane
        data->plane_x = data->plane_x * cos(rotation_amount) - data->plane_y * sin(rotation_amount);
        data->plane_y = old_plane_x * sin(rotation_amount) + data->plane_y * cos(rotation_amount);
        
        // Sync with the dir and plane arrays
        data->dir[X] = data->dir_x;
        data->dir[Y] = data->dir_y;
        data->plane[X] = data->plane_x;
        data->plane[Y] = data->plane_y;
		data->moved = 1;
    }
    
    // Center the mouse only if it's moved significantly
    if (abs(x - win_width/2) > 10)
    {
        mlx_mouse_move(data->mlx, data->win, win_width / 2, win_height / 2);
        data->mouse.prev_x = win_width / 2;
    }
    else
    {
        data->mouse.prev_x = x;
    }
    
    return (0);
}

int toggle_mouse_capture(int keycode, void *param)
{
    t_map_info *data = (t_map_info *)param;
    int win_width, win_height;
    
    if (keycode != 109) // Only proceed if it's the 'm' key
        return (0);
        
    data->mouse.is_captured = !data->mouse.is_captured;
    printf("Mouse capture toggled: %s (keycode: %d)\n",
           data->mouse.is_captured ? "ON" : "OFF", keycode);

    mlx_get_screen_size(data->mlx, &win_width, &win_height);

    if (data->mouse.is_captured)
    {
        mlx_mouse_move(data->mlx, data->win, win_width / 2, win_height / 2);
        data->mouse.prev_x = win_width / 2;
    }
    else
    {
        mlx_mouse_show(data->mlx, data->win);
    }
    
    return (0);
}

void init_mouse_controls(t_map_info *data)
{
    int win_width;
    int win_height;
    
    mlx_get_screen_size(data->mlx, &win_width, &win_height);
    
    data->mouse.prev_x = win_width / 2;
    data->mouse.x = win_width / 2;
    data->mouse.y = win_height / 2;
    data->mouse.is_captured = 0;
    
    data->rot_speed = 0.0002; // Adjust this value - 0.3 is too high
    
    printf("Mouse controls initialized. Press 'm' to toggle mouse capture.\n");
    
    // Only register the motion event here, not the keypress
    mlx_hook(data->win, MotionNotify, PointerMotionMask, handle_mouse_move, data);
}
