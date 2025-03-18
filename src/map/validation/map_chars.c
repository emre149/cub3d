/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:01:26 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 13:06:14 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	if (c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != 'D' && c != 'd')
		return (0);
	return (1);
}

static int	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	validate_char(char **map, int i, int j, int *player_count)
{
	if (!is_valid_char(map[i][j]))
	{
		printf("Error:\n Caractère invalide '%c' en position [%d,%d]\n",
			map[i][j], i, j);
		return (0);
	}
	if (is_player_char(map[i][j]))
		(*player_count)++;
	return (1);
}

static int	check_player_count(int player_count)
{
	if (player_count != 1)
	{
		printf("Error:\n Nombre de joueurs incorrect (%d trouvé).\n",
			player_count);
		return (0);
	}
	return (1);
}

int	check_valid_chars(char **map)
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
			if (!validate_char(map, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	return (check_player_count(player_count));
}
