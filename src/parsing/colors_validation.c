/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:06:50 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/04 15:16:11 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	count_commas(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	check_color_format(char *line, char *identifier)
{
	int	i;
	int	comma_count;
	int	digit_sections;

	i = 1;
	while (line[i] == ' ')
		i++;
	comma_count = count_commas(&line[i]);
	if (comma_count != 2)
	{
		printf("Error:\n Invalid RGB format for %s. Expected format: R,G,B\n", identifier);
		return (0);
	}
	digit_sections = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (ft_isdigit(line[i]))
		{
			digit_sections++;
			while (ft_isdigit(line[i]))
				i++;
		}
		else if (line[i] == ',' || line[i] == '\0' || line[i] == '\n')
			i++;
		else
		{
			printf("Error:\n Invalid character in RGB format for %s\n", identifier);
			return (0);
		}
	}
	if (digit_sections != 3)
	{
		printf("Error:\n Invalid RGB format for %s. Expected format: R,G,B\n", identifier);
		return (0);
	}
	return (1);
}
