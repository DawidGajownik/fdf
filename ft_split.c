/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgajowni <dgajowni@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:02:28 by dgajowni          #+#    #+#             */
/*   Updated: 2025/09/30 13:02:29 by dgajowni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	count_letters(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		j++;
		i++;
	}
	return (j);
}

static size_t	count_words(char const *s, char c)
{
	size_t		i;
	size_t		j;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		if (s[j])
		{
			i++;
			while (s[j] && s[j] != c)
				j++;
		}
	}
	return (i);
}

static char	**free_all(char **result, int i)
{
	int	j;

	j = 0;
	if (!result)
		return (NULL);
	while (j <= i)
	{
		free(result[j]);
		j++;
	}
	free(result);
	return (NULL);
}

static char	**malloc_all(char const *s, char c, int words)
{
	int		i;
	char	**result;

	i = 0;
	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	while (i < words)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			result[i] = malloc(count_letters(s, c) + 1);
			if (!result[i])
				return (free_all(result, i - 1));
		}
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = count_words(s, c);
	result = malloc_all(s, c, (int)i[2]);
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s == c && i[0] != 0 && i[1] < i[2] - 1)
		{
			result[i[1]++][i[0]] = '\0';
			i[0] = 0;
		}
		else if (*s != c)
			result[i[1]][i[0]++] = *s;
		s++;
	}
	if (i[0] != 0)
		result[i[1]][i[0]] = '\0';
	result[i[2]] = NULL;
	return (result);
}
