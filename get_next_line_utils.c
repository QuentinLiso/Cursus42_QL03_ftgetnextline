/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qliso <qliso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:44:52 by qliso             #+#    #+#             */
/*   Updated: 2024/11/21 14:44:53 by qliso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}

char *ft_strdup(const char *s)
{
		char *dest;
		size_t i;
		
		dest = malloc (ft_strlen(s) + 1);
		if (!dest)
				return (NULL);
		i = 0;
		while (s[i])
		{
				dest[i] = s[i];
				i++;
		}
		dest[i] = '\0';
		return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (siz <= dst_len)
		return (src_len + siz);
	i = 0;
	while (src[i] && i < siz - 1 - dst_len)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	dest = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	free(s1);
	free(s2);
	return (dest);
}

char *ft_strchr(const char *s, int c)
{
		char *ptr;
		char c_char;
		
		ptr = (char *) s;
		c_char = (char) c;
		while (*ptr && *ptr != c_char)
				ptr++;
		if (*ptr == c_char)
				return (ptr);
		else
				return (NULL);
}



