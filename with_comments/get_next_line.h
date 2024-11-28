/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qliso <qliso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:24:03 by qliso             #+#    #+#             */
/*   Updated: 2024/11/21 20:24:06 by qliso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
// 1 - On définit une macro BUFFER_SIZE avec ifndef car on est censé la définir à la compilation
// avec le flag -D BUFFER_SIZE=42
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

// 2 - Utilisation des 3 librairies stdlib.h (malloc, free), unistd.h (read, write) et fcntl.h (open, close)
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

// 3 - Prototypes des 8 fonctions utilisées
char	*get_next_line(int fd);
char	*set_buf_line(int fd, char *buf_line, char *buf_read);
char	*set_line(char *buf_line, char *line);
char	*offset_buf_line(char *buf_line);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

#endif
