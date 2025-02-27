/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:08:31 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/27 17:46:38 by ededemog         ###   ########.fr       */
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
		write(2, "Error: Doublon de la texture ", 29);
		write(2, identifier, ft_strlen(identifier));
		write(2, " détecté.\n", 11);
		return (0);
	}
	*texture = ft_strdup(&line[i]);
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
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		write(2, "Error: Valeur RGB invalide pour ", 33);
		write(2, identifier, ft_strlen(identifier));
		write(2, ". Les valeurs doivent être entre 0 et 255.\n", 43);
		return (0);
	}
	*color = (r << 16) | (g << 8) | b;
	return (1);
}

int	is_map_line(char *line)
{
	char	*trimmed;
	int		i;
	int		valid;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	i = 0;
	valid = 0;
	while (trimmed[i])
	{
		if (trimmed[i] == '1' || trimmed[i] == '0' || trimmed[i] == 'N'
			|| trimmed[i] == 'S' || trimmed[i] == 'E' || trimmed[i] == 'W')
			valid = 1;
		else if (trimmed[i] != ' ')
		{
			free(trimmed);
			return (0);
		}
		i++;
	}
	free(trimmed);
	return (valid);
}