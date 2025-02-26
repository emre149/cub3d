/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:34:15 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/12 22:30:35 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	get_map_bounds(char **map, int *start, int *end)
{
	int	i;

	*start = -1;
	*end = -1;
	i = 0;
	while (map[i])
	{
		if (is_map_line(map[i]))
		{
			if (*start == -1)
				*start = i;
			*end = i;
		}
		i++;
	}
	if (*start == -1)
		return (0);
	return (1);
}

static char	**duplicate_map_lines(char **map, int start, int end)
{
	char	**new_map;
	int		i;
	int		j;

	new_map = malloc(((end - start) + 2) * sizeof(char *));
	if (!new_map)
		return (NULL);
	i = start;
	j = 0;
	while (i <= end)
	{
		new_map[j] = ft_strdup(map[i]);
		if (!new_map[j])
		{
			free_map(new_map);
			return (NULL);
		}
		i++;
		j++;
	}
	new_map[j] = NULL;
	return (new_map);
}

void	parse_map_only(t_map_info *map_info)
{
	int		start;
	int		end;
	char	**new_map;

	if (!map_info->map)
		return ;
	if (!get_map_bounds(map_info->map, &start, &end))
		return ;
	new_map = duplicate_map_lines(map_info->map, start, end);
	if (!new_map)
		return ;
	free_map(map_info->map);
	map_info->map = new_map;
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

void detect_player(t_map_info *map_info)
{
    int i = 0;
    int j;

    while (map_info->map[i])
    {
        j = 0;
        while (map_info->map[i][j])
        {
            if (map_info->map[i][j] == 'N' || map_info->map[i][j] == 'S' ||
                map_info->map[i][j] == 'E' || map_info->map[i][j] == 'W')
            {
                // On stocke la position en pixels, ici en multipliant par 10 (selon la taille de tes cases)
                map_info->player_x = j * 10;
                map_info->player_y = i * 10;
                map_info->player_dir = map_info->map[i][j];
            }
            j++;
        }
        i++;
    }
}
