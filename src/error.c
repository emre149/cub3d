/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:51:11 by marvin            #+#    #+#             */
/*   Updated: 2025/02/26 09:51:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void delete_mlx(t_map_info *map_info)
{
    if (map_info->mlx)
        (free(map_info->mlx), mlx_destroy_window(map_info->mlx, map_info->win));
    if (map_info->win)
        mlx_destroy_display(map_info->mlx);
}

void error_exit(t_map_info *map_info, char *message)
{
    printf("Error\n%s\n", message);
    free_all(map_info);
    exit(1);
}


