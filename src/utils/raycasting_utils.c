/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:29 by ededemog          #+#    #+#             */
/*   Updated: 2025/04/02 11:07:05 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	**init_buff(t_map_info *map_info)
{
	int	**buf;
	int	i;

	i = 0;
	buf = ft_calloc(SCREEN_HEIGHT + 1, sizeof(int *));
	if (!buf)
		error_exit(map_info, "Buffer allocation failed");
	while (i < SCREEN_HEIGHT)
	{
		buf[i] = ft_calloc(SCREEN_WIDTH + 1, sizeof(int));
		if (!buf[i])
		{
			while (i >= 0)
				free(buf[i--]);
			free(buf);
			error_exit(map_info, "Buffer allocation failed");
		}
		i++;
	}
	return (buf);
}

void	step_sidedist(t_map_info *map_info)
{
	if (map_info->ray_dir[X] < 0)
	{
		map_info->step[X] = -1;
		map_info->side_dist[X] = (map_info->pos[X] - map_info->map_p[X])
			* map_info->ddist[X];
	}
	else
	{
		map_info->step[X] = 1;
		map_info->side_dist[X] = (map_info->map_p[X] + 1.0 - map_info->pos[X])
			* map_info->ddist[X];
	}
	if (map_info->ray_dir[Y] < 0)
	{
		map_info->step[Y] = -1;
		map_info->side_dist[Y] = (map_info->pos[Y] - map_info->map_p[Y])
			* map_info->ddist[Y];
	}
	else
	{
		map_info->step[Y] = 1;
		map_info->side_dist[Y] = (map_info->map_p[Y] + 1.0 - map_info->pos[Y])
			* map_info->ddist[Y];
	}
}

void	algo_dda(t_map_info *map_info)
{
	map_info->hit = 0;
	while (map_info->hit == 0)
	{
		if (map_info->side_dist[X] < map_info->side_dist[Y])
		{
			map_info->side_dist[X] += map_info->ddist[X];
			map_info->map_p[X] += map_info->step[X];
			map_info->side = X;
		}
		else
		{
			map_info->side_dist[Y] += map_info->ddist[Y];
			map_info->map_p[Y] += map_info->step[Y];
			map_info->side = Y;
		}
		if (map_info->map_p[X] < 0 || map_info->map_p[X] >= map_info->map_width
			/ 10 || map_info->map_p[Y] < 0
			|| map_info->map_p[Y] >= map_info->map_height / 10)
			break ;
		if (map_info->map[map_info->map_p[Y]][map_info->map_p[X]] == '1'
			|| map_info->map[map_info->map_p[Y]][map_info->map_p[X]] == \
			DOOR_CLOSE)
			map_info->hit = 1;
	}
}

static void	determine_texture(t_map_info *map_info)
{
	if (map_info->map[map_info->map_p[Y]][map_info->map_p[X]] == DOOR_CLOSE)
		map_info->tex_num = DOOR;
	else
	{
		if (map_info->side == 0)
		{
			if (map_info->ray_dir[X] < 0)
				map_info->tex_num = WE;
			else
				map_info->tex_num = EA;
		}
		else
		{
			if (map_info->ray_dir[Y] < 0)
				map_info->tex_num = NO;
			else
				map_info->tex_num = SO;
		}
	}
}

void	calc_dist(t_map_info *map_info)
{
	if (map_info->side == 0)
		map_info->wall_dist = (map_info->side_dist[X] - map_info->ddist[X]);
	else
		map_info->wall_dist = (map_info->side_dist[Y] - map_info->ddist[Y]);
	if (map_info->wall_dist <= 0.001)
		map_info->wall_dist = 0.001;
	map_info->line_height = (int)(SCREEN_HEIGHT / map_info->wall_dist);
	if (map_info->line_height > SCREEN_HEIGHT * 10)
		map_info->line_height = SCREEN_HEIGHT * 10;
	map_info->draw_start = -map_info->line_height / 2 + SCREEN_HEIGHT / 2;
	if (map_info->draw_start < 0)
		map_info->draw_start = 0;
	map_info->draw_end = map_info->line_height / 2 + SCREEN_HEIGHT / 2;
	if (map_info->draw_end >= SCREEN_HEIGHT)
		map_info->draw_end = SCREEN_HEIGHT - 1;
	determine_texture(map_info);
}
