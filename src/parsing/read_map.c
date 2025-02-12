/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:58:23 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/12 22:09:57 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_map_file(char *filename)
{
	int	len;

	len = strlen(filename);
	return (len > 4 && strcmp(filename + len - 4, ".cub") == 0);
}

static int	add_line(char ***lines, int *count, char *line)
{
	char	**temp;

	temp = (char **)ft_realloc(*lines, (*count + 2) * sizeof(char *));
	if (!temp)
	{
		free_map(*lines);
		free(line);
		return (0);
	}
	*lines = temp;
	(*lines)[*count] = line;
	(*lines)[*count + 1] = NULL;
	(*count)++;
	return (1);
}

static int	close_return(int fd)
{
	close(fd);
	return (0);
}

int	read_map_file(t_map_info *map_info, char *file_path)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	lines = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!add_line(&lines, &count, line))
			return (close_return(fd));
		line = get_next_line(fd);
	}
	close(fd);
	map_info->map = lines;
	return (1);
}
