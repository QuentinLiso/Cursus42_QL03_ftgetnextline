/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qliso <qliso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:47:52 by qliso             #+#    #+#             */
/*   Updated: 2024/11/21 14:47:54 by qliso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *set_buf_line(int fd, char *buf_line, char *buf_read)
{
	ssize_t	num_read;

	num_read = 1;
	if (!buf_line)
		buf_line = ft_strdup("");
	while(num_read > 0)
	{
		num_read = read(fd, buf_read, BUFFER_SIZE);
		if (num_read == -1)
		{
			free(buf_read);
			return (NULL);
		}
		buf_read[num_read] = '\0';
		buf_line = ft_strjoin(buf_line, buf_read);
		if (ft_strchr(buf_read, '\n'))
			break;
	}
	free(buf_read);
	return (buf_line);
}

static char *set_line(char *line, char *buf_line)
{
	unsigned int len;
	unsigned int i;

	if (!buf_line)
		return (NULL);
	len = 0;
	i = 0;
	while (buf_line[len] && buf_line[len] != '\n')
		len++;
	if (buf_line[len] == '\n')
		len++;
	line = malloc (len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = buf_line[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char *offset_buf_line(char *buf_line)
{
	char *dest;
	size_t start;
	size_t i;

	if (!buf_line)
		return (NULL);
	start = 0;
	i = 0;
	while (buf_line[start] && buf_line[start] != '\n')
		start++;
	if (buf_line[start] == '\n')
		start++;
	dest = malloc(ft_strlen(buf_line) - start + 1);
	if (!dest)
		return (NULL);
	while (buf_line[start + i])
	{
		dest[i] = buf_line[start + i];
		i++;
	}
	free(buf_line);
	dest[i] = '\0';
	return (dest);
}

static char *get_next_line(int fd)
{
	char *buf_read;
	static char *buf_line;
	char *line;

	line = NULL;
	buf_read = malloc (BUFFER_SIZE + 1);
	if (BUFFER_SIZE <= 0|| fd < 0 || read(fd, 0, 0) < 0)
	{
		free (buf_read);
		free (buf_line);
		buf_read = NULL;
		buf_line = NULL;
		return (NULL);
	}
	if (!buf_read)
		return (NULL);
	buf_line = set_buf_line (fd, buf_line, buf_read);
	if (*buf_line == 0)
	{
		free(buf_line);
		return (NULL);
	}
	line = set_line(line, buf_line);
	buf_line = offset_buf_line(buf_line);
	return (line);
}

int main()
{
	int fd = open("test.txt", O_RDWR);

	printf("%s\n\n\n", get_next_line(fd));
	printf("%s\n\n\n", get_next_line(fd));
	printf("%s\n\n\n", get_next_line(fd));
	printf("%s\n\n\n", get_next_line(fd));
	printf("%s\n\n\n", get_next_line(fd));
	printf("%s\n\n\n", get_next_line(fd));
	return (0);
}
