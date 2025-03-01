/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:36:19 by marvin            #+#    #+#             */
/*   Updated: 2025/02/26 10:40:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int **init_buff(t_map_info *map_info)
{
    int **buf;
    int i;

    i = 0;
    buf = ft_calloc(SCREEN_HEIGHT + 1, sizeof(int *));
    if (!buf)
        error_exit(map_info, "Error\nBuffer calloc\n");
    while (i < SCREEN_HEIGHT)
    {
        buf[i] = ft_calloc(SCREEN_WIDTH + 1, sizeof(int));
        if (!buf[i])
        {
            while (i >= 0)
                free(buf[i--]);
            free(buf);
            error_exit(map_info, "Error\nBuffer calloc\n");
        }
        i++;
    }
    return (buf);
}

void init_ray(t_map_info *map_info, int x)
{
    map_info->camerax[X] = 2 * x / (double)SCREEN_WIDTH - 1;
    map_info->ray_dir[X] = map_info->dir[X] + map_info->plane[X] * map_info->camerax[X];
    map_info->ray_dir[Y] = map_info->dir[Y] + map_info->plane[Y] * map_info->camerax[X];
    map_info->map_p[X] = (int)map_info->pos[X];
    map_info->map_p[Y] = (int)map_info->pos[Y];
    map_info->side_dist[X] = fabs(1 / map_info->ray_dir[X]);
    map_info->side_dist[Y] = fabs(1 / map_info->ray_dir[Y]);
}

void step_sidedist(t_map_info *map_info)
{
    if (map_info->ray_dir[X] < 0)
    {
        map_info->step[X] = -1;
        map_info->side_dist[X] = ((map_info->pos[X] - map_info->map_p[X]) * map_info->ddist[X]);
    }
    else
    {
        map_info->step[X] = 1;
        map_info->side_dist[X] = (map_info->map_p[X] + 1.0 - map_info->pos[X]) * map_info->ddist[X];
    }
    if (map_info->ray_dir[Y] < 0)
    {
        map_info->step[Y] = -1;
        map_info->side_dist[Y] = (map_info->pos[Y] - map_info->map_p[Y]) * map_info->ddist[Y];
    }
    else
    {
        map_info->step[Y] = 1;
        map_info->side_dist[Y] = (map_info->map_p[Y] + 1.0 - map_info->pos[Y]) * map_info->ddist[Y];
    }
}

void algo_dda(t_map_info *map_info)
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
        if (map_info->map_p[X] < 0.25 || map_info->map_p[X] > map_info->map_width - 1.25 || map_info->map_p[Y] < 0.25 || map_info->map_p[Y] > map_info->map_height - 1.25)
            break;
        if (map_info->map[map_info->map_p[Y]][map_info->map_p[X]] == '1')
            map_info->hit = 1;
    }
}

void calc_dist(t_map_info *map_info)
{
    if (map_info->side == 0)
        map_info->wall_dist = (map_info->side_dist[X] - map_info->ddist[X]);
    else
        map_info->wall_dist = (map_info->side_dist[Y] - map_info->ddist[Y]);
    map_info->line_height = (int)(SCREEN_HEIGHT / map_info->wall_dist);
    map_info->draw_start = -(map_info->line_height / 2) + SCREEN_HEIGHT / 2;
    if (map_info->draw_start < 0)
        map_info->draw_start = 0;
    map_info->draw_end = map_info->line_height / 2 + SCREEN_HEIGHT / 2;
    if (map_info->draw_end >= SCREEN_HEIGHT)
        map_info->draw_end = SCREEN_HEIGHT - 1;
    if (map_info->side)
    {
        if (map_info->ray_dir[X] < 0)
            map_info->tex_num = WE;
        else
            map_info->tex_num = EA;
    }
    else
    {
        if (map_info->ray_dir[Y] < 0)
            map_info->tex_num = SO;
        else
            map_info->tex_num = NO;
    }
}
