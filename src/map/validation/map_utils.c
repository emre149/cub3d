/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:07:47 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 13:09:34 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_directions(int directions[8][2])
{
	directions[0][0] = -1;
	directions[0][1] = 0;
	directions[1][0] = -1;
	directions[1][1] = 1;
	directions[2][0] = 0;
	directions[2][1] = 1;
	directions[3][0] = 1;
	directions[3][1] = 1;
	directions[4][0] = 1;
	directions[4][1] = 0;
	directions[5][0] = 1;
	directions[5][1] = -1;
	directions[6][0] = 0;
	directions[6][1] = -1;
	directions[7][0] = -1;
	directions[7][1] = -1;
}
