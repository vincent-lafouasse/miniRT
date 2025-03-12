/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:33:46 by poss              #+#    #+#             */
/*   Updated: 2025/03/12 01:33:36 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_n_words(char const *s, char c, size_t len);
static int		seek_next_word(const char *s, char c, int len, int start);
static int		seek_next_sep(const char *s, char c, int len, int start);
static void		*ft_free(char **s, int i);

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		start;
	int		end;
	int		len;
	int		out_index;

	len = ft_strlen(s);
	out = malloc((1 + get_n_words(s, c, len)) * sizeof(char *));
	if (out == NULL)
		return (NULL);
	out_index = 0;
	start = seek_next_word(s, c, len, 0);
	while (start != -1)
	{
		end = seek_next_sep(s, c, len, start);
		out[out_index] = ft_substr(s, start, end - start);
		if (out[out_index] == NULL)
			return (ft_free(out, out_index));
		start = seek_next_word(s, c, len, end);
		out_index++;
	}
	out[out_index] = NULL;
	return (out);
}

static size_t	get_n_words(char const *s, char c, size_t len)
{
	size_t	n;
	int		start;

	n = 0;
	start = seek_next_word(s, c, len, 0);
	while (start != -1)
	{
		n++;
		start = seek_next_sep(s, c, len, start);
		start = seek_next_word(s, c, len, start);
	}
	return (n);
}

static int	seek_next_word(const char *s, char c, int len, int start)
{
	while (s[start] == c && start < len)
	{
		start++;
	}
	if (start == len)
		return (-1);
	else
		return (start);
}

static int	seek_next_sep(const char *s, char c, int len, int start)
{
	while (s[start] != c && start < len)
	{
		start++;
	}
	return (start);
}

static void	*ft_free(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}
