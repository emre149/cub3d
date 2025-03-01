/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:52:34 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/01 15:24:20 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_texture_file(char *path)
{
	char *trimmed_path;
	int fd;
	int len;
	int result;

	trimmed_path = ft_strtrim(path, " \n\t");
	if (!trimmed_path || !*trimmed_path)
	{
		free(trimmed_path);
		printf("Error: Chemin de texture vide.\n");
		return (0);
	}
	printf("Vérification du chemin : '%s'\n", trimmed_path);

	fd = open(trimmed_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Fichier de texture introuvable : %s\n", trimmed_path);
		free(trimmed_path);
		return (0);
	}

	len = ft_strlen(trimmed_path);
	result = (len >= 4 && ft_strcmp(trimmed_path + len - 4, ".xpm") == 0);
	if (!result)
		printf("Error: Format de texture invalide (uniquement .xpm) : %s\n",
			trimmed_path);

	close(fd);
	free(trimmed_path);
	return (result);
}