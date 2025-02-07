/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:34:56 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/07 15:39:40 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	count_numbers(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

static int	check_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	validate_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (0);
		i++;
	}
	return (1);
}

static void	clean_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	parse_color(char *line)
{
	char **split;
	int rgb[3];
	int i;

	while (*line && ft_isspace(*line))
		line++;
	split = ft_split(line, ',');
	if (!split || count_numbers(split) != 3)
	{
		if (split)
			clean_split(split);
		return (-1);
	}
	i = 0;
	while (i < 3)
	{
		if (!check_valid_number(split[i]))
		{
			clean_split(split);
			return (-1);
		}
		rgb[i] = ft_atoi(split[i]);
		i++;
	}
	clean_split(split);
	if (!validate_rgb(rgb))
		return (-1);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}