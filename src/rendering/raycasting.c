/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:59 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/21 17:48:48 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	prepare_ray_calculation(t_map_info *map_info, int i)
{
	init_ray(map_info, i);
	step_sidedist(map_info);
	algo_dda(map_info);
	calc_dist(map_info);
}

static void	process_rays(t_map_info *map_info, int **buff)
{
	int	i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		prepare_ray_calculation(map_info, i);
		draw_line(map_info, buff, i);
		i++;
	}
}

void	raycasting(t_map_info *map_info)
{
	int		**buff;
	t_img	img;

	buff = init_buff(map_info);
	process_rays(map_info, buff);
	add_img(map_info, buff, &img);
	clean_buff(buff);
	draw_mini_map(map_info, map_info);
}
