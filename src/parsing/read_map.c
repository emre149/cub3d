/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:58:23 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/11 16:07:07 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_map_file(char *filename)
{
	int	len;

	len = strlen(filename);
	return (len > 4 && strcmp(filename + len - 4, ".cub") == 0);
}

int	read_map_file(t_map_info *map_info, char *file_path)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;
	char	**temp;

	count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	lines = NULL;
	while ((line = get_next_line(fd)))
	{
		temp = (char **)ft_realloc(lines, (count + 2) * sizeof(char *));
		if (!temp)
		{
			free_map(lines);
			free(line);
			close(fd);
			return (0);
		}
		lines = temp;
		lines[count++] = line;
		lines[count] = NULL;
	}
	close(fd);
	map_info->map = lines;
	return (1);
}

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

void	parse_texture(char **texture, char *line)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	*texture = ft_strdup(&line[i]);
}

void	parse_color(int *color, char *line)
{
	int	i;

	i = 1;
	int r, g, b;
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
	*color = (r << 16) | (g << 8) | b;
}

void	parse_map_only(t_map_info *map_info)
{
	int		i;
	char	*line;

	i = 0;
	while (map_info->map[i])
	{
		line = map_info->map[i];
		if (is_map_line(line))
		{
			map_info->map = &map_info->map[i];
			return ;
		}
		i++;
	}
}

int	parse_config(t_map_info *map_info)
{
	int i = 0;
	while (map_info->map[i])
	{
		char *line = map_info->map[i];
		if (strncmp(line, "R ", 2) == 0)
			parse_resolution(map_info, line);
		else if (strncmp(line, "NO ", 3) == 0)
			parse_texture(&map_info->no_texture, line);
		else if (strncmp(line, "SO ", 3) == 0)
			parse_texture(&map_info->so_texture, line);
		else if (strncmp(line, "WE ", 3) == 0)
			parse_texture(&map_info->we_texture, line);
		else if (strncmp(line, "EA ", 3) == 0)
			parse_texture(&map_info->ea_texture, line);
		else if (strncmp(line, "S ", 2) == 0)
			parse_texture(&map_info->sprite, line);
		else if (strncmp(line, "F ", 2) == 0)
			parse_color(&(map_info->floor_color), line);
		else if (strncmp(line, "C ", 2) == 0)
			parse_color(&(map_info->ceiling_color), line);
		else if (is_map_line(line))
		{
			parse_map_only(map_info);
			break ;
		}
		i++;
	}
	return (1);
}


int is_map_line(char *line)
{
    while (*line)
    {
        if (*line != ' ' && *line != '1' && *line != '0' &&
            *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
            return (0);
        line++;
    }
    return (1);
}