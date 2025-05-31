/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:25:35 by ikulik            #+#    #+#             */
/*   Updated: 2025/05/31 18:06:15 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		diff;
	size_t	index;

	diff = 0;
	index = 0;
	while (*s1 && *s2 && index < n)
	{
		if (*s1 != *s2)
		{
			diff = (unsigned char)*s1 - (unsigned char)*s2;
			return (diff);
		}
		s1++;
		s2++;
		index++;
	}
	if (index < n)
		diff = (unsigned char)*s1 - (unsigned char)*s2;
	return (diff);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	length;

	length = 0;
	index = 0;
	while (src[length])
		length++;
	if (size > 0)
	{
		while (src[index] && (index < size - 1))
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (length);
}

void	*clean_split(char **str)
{
	char	**start;

	start = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(start);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*result;
	size_t	len_s1;
	size_t	len_s2;
	size_t	len_s3;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	len_s3 = ft_strlen(s3);
	result = (char *)malloc((len_s1 + len_s2 + len_s3 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len_s1 + 1);
	ft_strlcpy(&result[len_s1], s2, len_s2 + 1);
	ft_strlcpy(&result[len_s1 + len_s2], s3, len_s3 + 1);
	return (result);
}
