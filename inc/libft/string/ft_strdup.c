/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:26:20 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *str)
{
	int		str_len;
	char	*new;

	str_len = ft_strlen(str);
	new = malloc(sizeof(char) * (str_len + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, str, str_len + 1);
	return (new);
}
/*
#include <stdio.h>

int	main()
{
	const char str[] = "bonjour emre";

	printf("%s", ft_strdup(str));
}
*/