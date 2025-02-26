/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:21:11 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strndup( const char *source, size_t size )
{
	char	*new;

	new = malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, source, size + 1);
	return (new);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, *start))
		start++;
	if (!*start)
		return (ft_strdup(""));
	end = start + ft_strlen(start);
	while (end > start && ft_strchr(set, *end))
		end--;
	len = (end - start) + 1;
	return (ft_strndup(start, len));
}
