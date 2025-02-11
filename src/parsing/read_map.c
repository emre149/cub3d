/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:58:23 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/11 19:29:17 by ededemog         ###   ########.fr       */
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
	int r;
	int g;
	int b;

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
	*color = (r << 16) | (g << 8) | b;
}

void	parse_map_only(t_map_info *map_info)
{
	int		i;
	int		j;
	int		map_start;
	int		map_end;
	char	**new_map;
	int		map_size;

	i = 0;
	i = 0;
	j = 0;
	map_start = -1;
	map_end = -1;
	if (!map_info->map)
		return ;
	while (map_info->map[i])
	{
		if (is_map_line(map_info->map[i]))
		{
			if (map_start == -1)
				map_start = i;
			map_end = i;
		}
		i++;
	}
	if (map_start == -1)
		return ;
	map_size = map_end - map_start + 1;
	new_map = malloc((map_size + 1) * sizeof(char *));
	if (!new_map)
		return ;
	for (i = map_start; i <= map_end; i++)
	{
		new_map[j] = ft_strdup(map_info->map[i]);
		if (!new_map[j])
		{
			free_map(new_map);
			return ;
		}
		j++;
	}
	new_map[j] = NULL;
	free_map(map_info->map);
	map_info->map = new_map;
}

int	parse_config(t_map_info *map_info)
{
	int		i;
	char	*line;

	i = 0;
	while (map_info->map[i])
	{
		line = map_info->map[i];
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
int	is_map_line(char *line)
{
	char	*trimmed;
	int		i;
	int		valid;

	i = 0;
	valid = 0;
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	while (trimmed[i])
	{
		if (trimmed[i] == '1' || trimmed[i] == '0' || trimmed[i] == 'N'
			|| trimmed[i] == 'S' || trimmed[i] == 'E' || trimmed[i] == 'W')
		{
			valid = 1;
		}
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
