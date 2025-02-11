/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:39:54 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strstr(char *haystack, char *needle)
{
	int		i;
	char	*temp;

	temp = haystack;
	if (!*needle)
		return (haystack);
	while (*temp)
	{
		i = 0;
		if (*temp == needle[0])
		{
			while (temp[i] == needle[i] && needle[i])
				i++;
			if (needle[i] == '\0')
				return (temp);
		}
		temp++;
	}
	return (0);
}
