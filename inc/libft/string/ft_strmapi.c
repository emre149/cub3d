/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 07:28:59 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*new;

	i = 0;
	if (!s || !f)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (i < ft_strlen(s))
	{
		new[i] = (*f)(i, s[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}
