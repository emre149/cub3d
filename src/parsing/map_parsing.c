/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:36:31 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/03 15:17:06 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*clean_line(char *line)
{
	int		i;
	char	*cleaned;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	cleaned = ft_strtrim(line, " \t");
	free(line);
	return (cleaned);
}

static int	add_line(char ***lines, int *count, char *line)
{
	char	**temp;
	int		i;

	temp = (char **)malloc((*count + 2) * sizeof(char *));
	if (!temp)
	{
		free_map(*lines);
		free(line);
		return (0);
	}
	i = 0;
	while (i < *count)
	{
		temp[i] = (*lines)[i];
		i++;
	}
	temp[*count] = line;
	temp[*count + 1] = NULL;
	if (*lines)
		free(*lines);
	*lines = temp;
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
	char	*cleaned_line;
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
		cleaned_line = clean_line(line);
		if (cleaned_line && *cleaned_line)
		{
			if (!add_line(&lines, &count, cleaned_line))
				return (close_return(fd));
		}
		else
			free(cleaned_line);
		line = get_next_line(fd);
	}
	close(fd);
	map_info->map = lines;
	return (1);
}
