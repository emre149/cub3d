/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:34:15 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/01 17:32:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
			while (j > 0)
				free(new_map[--j]);
			free(new_map);
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
    int i;
    int j;

    if (!map_info || !map_info->map)
        error_exit(map_info, "No map loaded");
        
    i = 0;
    while (map_info->map[i])
    {
        j = 0;
        while (map_info->map[i][j])
        {
            if (map_info->map[i][j] == 'N' || map_info->map[i][j] == 'S' ||
                map_info->map[i][j] == 'E' || map_info->map[i][j] == 'W')
            {
                map_info->player_x = j;
                map_info->player_y = i;
                map_info->player_dir = map_info->map[i][j];
                return;
            }
            j++;
        }
        i++;
    }
    error_exit(map_info, "No player found in map");
}
