/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:20:10 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:00:47 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	safe_malloc(char **word_v, int pos, size_t buffer)
{
	int	i;

	i = 0;
	word_v[pos] = malloc(buffer);
	if (NULL == word_v[pos])
	{
		while (i < pos)
			free(word_v[i++]);
		free(word_v);
		return (1);
	}
	return (0);
}

static size_t	count_words(char const *s, char delimeter)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != delimeter) || (i > 0 && s[i] != delimeter
				& s[i - 1] == delimeter))
			words++;
		i++;
	}
	return (words);
}

static int	fill(char **word_v, char const *s, char delimeter)
{
	size_t	len;
	size_t	pos;

	pos = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimeter && *s)
			++s;
		while (*s != delimeter && *s)
		{
			++len;
			++s;
		}
		if (len)
		{
			if (safe_malloc(word_v, pos, len + 1))
				return (1);
			ft_strlcpy(word_v[pos], s - len, len + 1);
		}
		++pos;
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	size_t	words;
	char	**word_v;

	if (NULL == s)
		return (NULL);
	words = 0;
	words = count_words(s, c);
	word_v = malloc((words + 1) * sizeof(char *));
	if (!word_v)
		return (NULL);
	word_v[words] = NULL;
	if (fill(word_v, s, c))
		return (NULL);
	return (word_v);
}
