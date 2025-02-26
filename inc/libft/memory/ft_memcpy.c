/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:05:23 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/11 16:19:03 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
    unsigned char	*dest_temp;
    unsigned char	*src_temp;

    if (!dest || !src)
        return (NULL);
    dest_temp = (unsigned char *)dest;
    src_temp = (unsigned char *)src;
    while (size > 0)
    {
        *(dest_temp++) = *(src_temp++);
        size--;
    }
    return (dest);
}
