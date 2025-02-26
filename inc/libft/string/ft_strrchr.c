/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:58:55 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int searchedChar)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (str[++i])
	{
		if (str[i] == (char)searchedChar)
			temp = (char *)&str[i];
	}
	if (!str[i] && searchedChar == '\0')
		return ((char *)&str[i]);
	return (temp);
}
/*
#include <stdio.h>
#include <string.h>

int	main()
{
	const char str[] = "bonjour emre";
	int searched = 'b';

	printf("%s\n", ft_strrchr(str, searched));
	printf("%s", strrchr(str, searched));
}
*/