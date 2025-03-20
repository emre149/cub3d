/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:14:59 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/20 21:11:58 by ededemog         ###   ########.fr       */
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

static void	log_ray_info(t_map_info *map_info, int i)
{
	if (i == SCREEN_WIDTH / 2)
	{
		printf("Texture sélectionnée pour le rayon central: %d\n",
			map_info->tex_num);
		printf("Coordonnées de texture: X=%d, Y=%d\n", map_info->tex[X],
			map_info->tex[Y]);
	}
}

static void	process_rays(t_map_info *map_info, int **buff)
{
	int	i;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		prepare_ray_calculation(map_info, i);
		log_ray_info(map_info, i);
		draw_line(map_info, buff, i);
		i++;
	}
}

void	raycasting(t_map_info *map_info)
{
	int		**buff;
	t_img	img;

	printf("Initialisation du buffer...\n");
	buff = init_buff(map_info);
	printf("Début du raycasting...\n");
	process_rays(map_info, buff);
	printf("Ajout de l'image à la fenêtre...\n");
	add_img(map_info, buff, &img);
	printf("Nettoyage du buffer...\n");
	clean_buff(buff);
	printf("Dessin de la mini-map...\n");
	draw_mini_map(map_info, map_info);
	printf("Raycasting terminé avec succès.\n");
}
