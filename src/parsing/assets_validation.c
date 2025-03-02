/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:52:34 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/02 14:23:24 by ededemog         ###   ########.fr       */
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
		write(2, "Error: Chemin de texture vide.\n", 32);
		return (0);
	}
	write(1, "Vérification du chemin : '", 27);
	write(1, trimmed_path, ft_strlen(trimmed_path));
	write(1, "'\n", 2);

	fd = open(trimmed_path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error: Fichier de texture introuvable : ", 40);
		write(2, trimmed_path, ft_strlen(trimmed_path));
		write(2, "\n", 1);
		free(trimmed_path);
		return (0);
	}

	len = ft_strlen(trimmed_path);
	result = (len >= 4 && ft_strcmp(trimmed_path + len - 4, ".xpm") == 0);
	if (!result)
	{
		write(2, "Error: Format de texture invalide (uniquement .xpm) : ", 54);
		write(2, trimmed_path, ft_strlen(trimmed_path));
		write(2, "\n", 1);
	}

	close(fd);
	free(trimmed_path);
	return (result);
}