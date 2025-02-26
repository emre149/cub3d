/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:17:25 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/11 16:18:16 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!ptr)
		return (malloc(size));
	if (!size)
	{
		ft_memdel(&ptr);
		return (ptr);
	}
	new = malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, size);
	ft_memdel(&ptr);
	return (new);
}
