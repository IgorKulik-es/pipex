/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:26:16 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/06 19:19:35 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	word_count(char const *str, char space)
{
	size_t	count;
	int		flag;

	flag = 1;
	count = 0;
	while (*str)
	{
		if (flag && *str != space)
		{
			count++;
			flag = 0;
		}
		if (*str == space)
			flag = 1;
		str++;
	}
	return (count);
}

static char	**initialize(int *flag, size_t *i, char ***result, size_t words)
{
	*flag = 1;
	*i = 0;
	if (words > 0)
		*result = (char **)malloc((words + 1) * sizeof(char *));
	else
		*result = (char **)malloc(2 * sizeof(char *));
	if (*result == NULL)
		return (NULL);
	(*result)[words] = NULL;
	if (words == 0)
	{
		(*result)[1] = NULL;
		(*result)[0] = malloc(1 * sizeof(char));
		(*result)[0][0] = '\0';
	}
	return (*result);
}

static void	mark_word_start(int *flag, size_t *len, char **buf, char const *s)
{
	*flag = 0;
	*buf = (char *)s;
	*len = 1;
}

static char	*asign_line(char **result, char *buffer, size_t *i_w, size_t len)
{
	size_t	index;

	index = 0;
	result[*i_w] = (char *)malloc((len + 1) * sizeof (char));
	if (result[*i_w] == NULL)
	{
		while (index < *i_w)
		{
			free(result[index]);
			index++;
		}
		free(result);
		return (NULL);
	}
	ft_strlcpy(result[*i_w], buffer, len + 1);
	*i_w = *i_w + 1;
	return (result[*i_w - 1]);
}

char	**ft_split(char const *s, char c, int *words)
{
	size_t	index_word;
	size_t	len;
	char	**result;
	char	*buffer;
	int		flag;

	*words = word_count(s, c);
	if (initialize(&flag, &index_word, &result, *words) == NULL)
		return (NULL);
	while (*s)
	{
		if (flag == 1 && *s != c)
			mark_word_start(&flag, &len, &buffer, s);
		else if (flag == 0 && *s != c)
			len++;
		if (flag == 0 && (*s == c || (*(s + 1) == 0)))
		{
			if (asign_line(result, buffer, &index_word, len) == NULL)
				return (NULL);
			flag = 1;
		}
		s++;
	}
	return (result);
}
