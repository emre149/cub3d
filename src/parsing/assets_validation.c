/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:52:34 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/04 15:14:40 by ededemog         ###   ########.fr       */
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
		printf("Error:\n Empty texture path\n");
		return (0);
	}
	fd = open(trimmed_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error:\n Texture file not found: %s\n", trimmed_path);
		free(trimmed_path);
		return (0);
	}

	len = ft_strlen(trimmed_path);
	result = (len >= 4 && ft_strcmp(trimmed_path + len - 4, ".xpm") == 0);
	if (!result)
	{
		printf("Error:\n Invalid texture file format (only .xpm): %s\n", trimmed_path);
		printf("%s\n", trimmed_path);
	}
	close(fd);
	free(trimmed_path);
	return (result);
}