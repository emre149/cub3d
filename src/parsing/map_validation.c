/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:37:30 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/02 16:25:19 by ededemog         ###   ########.fr       */
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

static int	check_valid_chars(char **map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W')
			{
				write(2, "Error: Caractère invalide '", 28);
				ft_putchar_fd(map[i][j], 2);
				write(2, "' en position [", 15);
				ft_putnbr_fd(i, 2);
				write(2, ",", 1);
				ft_putnbr_fd(j, 2);
				write(2, "]\n", 2);
				return (0);
			}
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		write(2, "Error: Nombre de joueurs incorrect (", 36);
		ft_putnbr_fd(player_count, 2);
		write(2, " trouvé).\n", 11);
		return (0);
	}
	return (1);
}

static int	is_empty_or_edge(char **map, int i, int j)
{
	if (i < 0 || j < 0 || !map[i] || j >= (int)ft_strlen(map[i])
		|| map[i][j] == ' ')
		return (1);
	return (0);
}

static int	is_surrounded(char **map, int i, int j)
{
	int	directions[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1},
			{0, -1}, {-1, -1}};
	int	k;
	int	new_i;
	int	new_j;

	k = 0;
	while (k < 8)
	{
		new_i = i + directions[k][0];
		new_j = j + directions[k][1];
		if (is_empty_or_edge(map, new_i, new_j))
		{
			write(2, "Error: Carte non fermée en position [", 38);
			ft_putnbr_fd(i, 2);
			write(2, ",", 1);
			ft_putnbr_fd(j, 2);
			write(2, "] (caractère '", 14);
			ft_putchar_fd(map[i][j], 2);
			write(2, "').\n", 4);
			return (0);
		}
		k++;
	}
	return (1);
}

static int	check_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!is_surrounded(map, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void	normalize_map(char **map, t_map_info *map_info)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				map_info->player_dir = map[i][j];
				map_info->player_x = j * 10;
				map_info->player_y = i * 10;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

static void	restore_player(t_map_info *map_info)
{
	int	i;
	int	j;

	i = map_info->player_y / 10;
	j = map_info->player_x / 10;
	if (i >= 0 && j >= 0 && map_info->map[i]
		&& j < (int)ft_strlen(map_info->map[i]))
		map_info->map[i][j] = map_info->player_dir;
}

static void init_player_direction(t_map_info *map_info)
{
    if (map_info->player_dir == 'N')
    {
        map_info->dir[X] = 0;
        map_info->dir[Y] = -1;
        map_info->plane[X] = 0.66;
        map_info->plane[Y] = 0;
    }
    else if (map_info->player_dir == 'S')
    {
        map_info->dir[X] = 0;
        map_info->dir[Y] = 1;
        map_info->plane[X] = -0.66;
        map_info->plane[Y] = 0;
    }
    else if (map_info->player_dir == 'E')
    {
        map_info->dir[X] = 1;
        map_info->dir[Y] = 0;
        map_info->plane[X] = 0;
        map_info->plane[Y] = 0.66;
    }
    else if (map_info->player_dir == 'W')
    {
        map_info->dir[X] = -1;
        map_info->dir[Y] = 0;
        map_info->plane[X] = 0;
        map_info->plane[Y] = -0.66;
    }
    
    map_info->dir_x = map_info->dir[X];
    map_info->dir_y = map_info->dir[Y];
    map_info->plane_x = map_info->plane[X];
    map_info->plane_y = map_info->plane[Y];
    
    map_info->pos[X] = (double)map_info->player_x / 10;
    map_info->pos[Y] = (double)map_info->player_y / 10;
}

int	validate_map(t_map_info *map_info)
{
	if (!map_info->map)
	{
		write(2, "Error: Aucune carte à valider.\n", 32);
		return (0);
	}

	if (!check_valid_chars(map_info->map))
		return (0);

	normalize_map(map_info->map, map_info);

	if (!check_map_closed(map_info->map))
	{
		restore_player(map_info);
		return (0);
	}

	restore_player(map_info);
	
	init_player_direction(map_info);

	return (1);
}