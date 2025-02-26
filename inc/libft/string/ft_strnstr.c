/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 22:14:16 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (len > 0 && haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && i + j < len && haystack[i + j] == needle[j])
		{
			j++;
			if (!needle[j])
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>

int	main()
{
	const char hay[] = "";
	const char need[] = "emre";

	printf("%s", ft_strnstr(hay, need, 15));
}
*/