/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:23:03 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *pointer, size_t count)
{
	size_t	i;
	int		value;

	i = 0;
	value = 0;
	while (i < count)
	{
		*(unsigned char *)(pointer + i) = (unsigned char)value;
		i++;
	}
}
/*
#include <stdio.h>

int	main()
{
	char mem[50];
	ft_bzero(mem, 50);
	for (int i = 0; i < 50; i++)
		printf("%c", mem[i]);
	printf("\n");
	return 0;
}
*/