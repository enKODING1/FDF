/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:12:49 by skang             #+#    #+#             */
/*   Updated: 2024/10/18 23:12:00 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_character_count(char *s, char c)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			break ;
		index++;
	}
	return (index);
}

static int	get_separator_count(char *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (s[index] != '\0')
	{
		if (s[index] == c)
			count++;
		index++;
	}
	return (count);
}

static char	**free_ptr(char **ptr, int col_size)
{
	int	i;

	i = -1;
	while (++i < col_size)
	{
		free(ptr[i]);
	}
	free(ptr);
	return (NULL);
}

static char	**write_split(char const *s, char **s_ptr, int separator_len,
		char c)
{
	int	index;
	int	charactor_count;
	int	s_ptr_idx;

	index = 0;
	charactor_count = 0;
	s_ptr_idx = -1;
	while (separator_len-- > 0)
	{
		charactor_count = get_character_count((char *)&s[index], c);
		if (charactor_count > 0)
			s_ptr[++s_ptr_idx] = ft_substr((char *)&s[index], 0,
					(size_t)charactor_count);
		if (s_ptr[s_ptr_idx] == NULL)
			return (free_ptr(&s_ptr[0], get_separator_count((char *)s, c) + 2));
		index = index + charactor_count + 1;
	}
	s_ptr[++s_ptr_idx] = NULL;
	return (s_ptr);
}

char	**ft_split(char const *s, char c)
{
	int		separator_len;
	char	**s_ptr;

	if (!s)
		return (NULL);
	separator_len = get_separator_count((char *)s, c) + 1;
	s_ptr = (char **)malloc(sizeof(char *) * (separator_len + 1));
	if (!s_ptr)
		return (NULL);
	if (write_split(s, s_ptr, separator_len, c) == NULL)
		return (NULL);
	return (s_ptr);
}
