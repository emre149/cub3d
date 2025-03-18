/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:08:31 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 15:30:07 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	parse_resolution(t_map_info *map_info, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	map_info->map_width = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	map_info->map_height = ft_atoi(&line[i]);
}

int	parse_texture(char **texture, char *line, char *identifier)
{
	int	i;

	i = ft_strlen(identifier);
	while (line[i] == ' ')
		i++;
	if (*texture != NULL)
	{
		printf("Error:\n Doublon de la texture %s détecté.\n", identifier);
		return (0);
	}
	*texture = ft_strdup(&line[i]);
	return (1);
}

static int	validate_rgb_values(int r, int g, int b, char *identifier)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error:\n Valeur RGB invalide pour %s.\n", identifier);
		return (0);
	}
	return (1);
}

int	parse_color(int *color, char *line, char *identifier)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (!check_color_format(line, identifier))
		return (0);
	i = 1;
	while (line[i] == ' ')
		i++;
	r = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	g = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ' || line[i] == ',')
		i++;
	b = ft_atoi(&line[i]);
	if (!validate_rgb_values(r, g, b, identifier))
		return (0);
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

int	is_map_line(char *line)
{
	int	i;
	int	valid;

	if (!line || !*line)
		return (0);
	i = 0;
	valid = 0;
	while (line[i])
	{
		if (line[i] == '1')
			valid = 1;
		else if (line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (valid);
}
