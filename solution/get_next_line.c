/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbian <lfabbian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:43:10 by lfabbian          #+#    #+#             */
/*   Updated: 2022/12/04 16:55:09 by lfabbian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf_read;
	static char	*buf_line;
	char		*line;

	line = NULL;
	buf_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buf_line);
		free(buf_read);
		buf_line = NULL;
		buf_read = NULL;
		return (NULL);
	}
	if (!buf_read)
		return (NULL);
	buf_line = set_buf_line(fd, buf_line, buf_read);
	if (*buf_line == 0)
	{
		free (buf_line);
		return (buf_line = 0);
	}
	line = set_line(buf_line, line);
	buf_line = offset_buf_line(buf_line);
	return (line);
}

char	*set_buf_line(int fd, char *buf_line, char *buf_read)
{
	ssize_t	nbytes;

	nbytes = 1;
	if (!buf_line)
		buf_line = ft_strdup("");
	while (nbytes > 0)
	{
		nbytes = read(fd, buf_read, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free (buf_read);
			return (NULL);
		}
		buf_read[nbytes] = '\0';
		buf_line = ft_strjoin (buf_line, buf_read);
		if ((ft_strchr(buf_read, '\n')))
			break ;
	}
	free (buf_read);
	return (buf_line);
}

char	*set_line(char *buf_line, char *line)
{
	int	start;
	int	i;

	start = 0;
	i = 0;
	if (!buf_line)
		return (NULL);
	while (buf_line[start] != '\n' && buf_line[start])
		start++;
	if (buf_line[start] == '\n')
		start++;
	line = malloc((start + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (i < start)
	{
		line[i] = buf_line[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*offset_buf_line(char	*buf_line)
{
	char	*new_bline;
	int		start;
	int		i;

	start = 0;
	i = 0;
	if (!buf_line)
		return (NULL);
	while (buf_line[start] != '\n' && buf_line[start])
		start++;
	if (buf_line[start] == '\n')
		start++;
	new_bline = malloc((ft_strlen(buf_line) - start + 1) * sizeof(char));
	if (!new_bline)
		return (NULL);
	while (buf_line[start + i])
	{
		new_bline[i] = buf_line[start + i];
		i++;
	}
	free (buf_line);
	new_bline[i] = '\0';
	return (new_bline);
}

int main()
{
	int	fd;

	fd = open("text.txt", O_RDONLY);
	printf("GNL 1: %s", get_next_line(fd));
	printf("GNL 2: %s", get_next_line(fd));
	printf("GNL 3: %s", get_next_line(fd));
	printf("GNL 4: %s", get_next_line(fd));
	printf("GNL 5: %s", get_next_line(fd));
	printf("GNL 6: %s", get_next_line(fd));
	printf("GNL 7: %s", get_next_line(fd));
	printf("GNL 8: %s", get_next_line(fd));
	printf("GNL 9: %s", get_next_line(fd));
	printf("GNL 10: %s", get_next_line(fd));
	printf("GNL 11: %s", get_next_line(fd));
	printf("GNL 12: %s", get_next_line(fd));
	close(fd);
}