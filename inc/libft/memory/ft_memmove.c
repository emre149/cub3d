/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:22:42 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*dest_temp;
	unsigned char	*src_temp;
	size_t			i;

	i = 0;
	dest_temp = (unsigned char *)dest;
	src_temp = (unsigned char *)src;
	if (dest_temp > src_temp)
		while (len-- > 0)
			dest_temp[len] = src_temp[len];
	else
	{
		while (i < len)
		{
			dest_temp[i] = src_temp[i];
			i++;
		}
	}
	return (dest);
}
