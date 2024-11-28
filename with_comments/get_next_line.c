/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qliso <qliso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:23:53 by qliso             #+#    #+#             */
/*   Updated: 2024/11/21 20:23:56 by qliso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 1 - Fonction get_next_line qui prend 1 paramètre int correspondant à un fd
// et retourne la prochaine ligne (jusqu'à un \n) de ce fd
char	*get_next_line(int fd)
{
	// 1.1 - On définit 3 variables : 1 char * pour le buffer de la fonction read
	// 1 static char * correspondant à la ligne totale en buffer jusqu'à ce qu'on rencontre un \n ou la fin de la chaine
	// (cette chaine peut avoir des caractères qui dépassent le \n, mais nous on veut afficher que jusqu'au \n)
	// 1 char * correspondant à la ligne qu'on veut afficher
	char		*buf_read;
	static char	*buf_line;
	char		*line;

	// 1.2 - On initialise à NULL la chaîne qu'on veut afficher
	line = NULL;
	// 1.3 - On initialise le buffer pour read avec malloc sur la taille de buffer choisie +1
	// L'initialisation se fait avant le check 1.4 car on ne peut pas free buf_read s'il n'est pas malloc
	buf_read = malloc((BUFFER_SIZE + 1) * sizeof(char));
	// 1.4 - Premier contrôle sur le fd, la taille du buffer ou l'échec de read le fd
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		// 1.5 - On libère buf_line et buf_read
		free(buf_line);
		free(buf_read);
		// 1.6 - On leur assigne NULL
		buf_line = NULL;
		buf_read = NULL;
		// 1.7 - get_next_line retourne NULL
		return (NULL);
	}
	// 1.8 - Contrôle sur le malloc de buf_read
	if (!buf_read)
		return (NULL);
	// 1.9 - On assigne buf_line en appelant de set_buf_line sur le fd, avec les variables buf_line et buf_read (voir 2 pour l'explication de la fonction)
	buf_line = set_buf_line(fd, buf_line, buf_read);
	// 1.10 - Contrôle si buf_line est une chaîne vide (*buf_line = '\0')
	if (*buf_line == 0)
	{
		// 1.11 - On libère buf_line et on lui assigne NULL avant de la retourner
		free (buf_line);
		return (buf_line = 0);
	}
	// 1.12 - On assigne line (ligne à afficher par gnl) en appelant set_line sur buf_line et line (voir 3 pour l'explication de la fonction)
	line = set_line(buf_line, line);
	// 1.13 - On décale buf_line en appelant offset_buf_line sur buf_line (voir 4 pour l'explication de la fonction)
	buf_line = offset_buf_line(buf_line);
	return (line);
}

// 2 - Fonction set_buf_line qui prend 3 paramètres : int correspondant au fd, char * correspondant à la ligne qui est dans le buffer
// et char * correspondant au buffer utilisé pour la fonction read
// La fonction renvoie son 2ème paramètre après avoir concaténé son 2ème (buf_line) et son 3ème paramètre (buf_read)
// Elle concatène tant qu'il n'y a pas de \n dans buf_read
char	*set_buf_line(int fd, char *buf_line, char *buf_read)
{
	// 2.1 - On définit une variable ssize_t (signed size_t) pour mesurer le nb de bytes lus par read
	ssize_t	nbytes;

	// 2.2 - On initialise la variable à 1 pour rentrer au moins 1 fois dans la boucle ci-après
	nbytes = 1;
	// 2.3 - Contrôle si buf_line est NULL, alors on la fait pointer vers une chaîne vide
	if (!buf_line)
		buf_line = ft_strdup("");
	// 2.4 - Boucle tant qu'on lit un nb de bytes > 0
	while (nbytes > 0)
	{
		// 2.5 - On assigne à nbytes le résultat de lecture de BUFFER_SIZE dans buf_read
		nbytes = read(fd, buf_read, BUFFER_SIZE);
		// 2.6 - Contrôle si nbytes = -1 (i.e. lecture échouée)
		if (nbytes == -1)
		{
			// 2.7 - On libère le buffer et on retourne NULL
			free (buf_read);
			return (NULL);
		}
		// 2.8 - On rajoute le caractère nul à la fin du buf_read
		buf_read[nbytes] = '\0';
		// 2.9 - On concatène buf_line et buf_read
		buf_line = ft_strjoin (buf_line, buf_read);
		// 2.10 - On définit une condition de sortie de boucle (break) s'il y a un \n dans buf_read
		if ((ft_strchr(buf_read, '\n')))
			break ;
	}
	// 2.11 - On libère buf_read
	free (buf_read);
	// 2.12 - On retourne buf_line (qui correspond à la concaténation de tous les buf_read jusqu'à rencontrer un \n)
	return (buf_line);
}

// 3 - Fonction set_line qui prend 2 paramètres : char * correspondant à la ligne en buffer 
// et char * correspondant à la ligne à afficher dans get_next_line
// La fonction va mettre buf_line dans line jusqu'au premier \n rencontré ou jusqu'à la fin de buf_line
char	*set_line(char *buf_line, char *line)
{
	// 3.1 - On définit 2 variables : 1 int pour indiquer le derniere emplacement de buf_line (\n ou \0)
	// et 1 int pour parcourir line
	int	buf_end;
	int	i;

	// 3.2 - On initialise les 2 variables à 0
	buf_end = 0;
	i = 0;
	// 3.3 - Contrôle retourner NULL si buf_line est NULL
	if (!buf_line)
		return (NULL);
	// 3.4 - Boucle while pour décaler tant qu'on ne rencontre pas de \n ou \0
	while (buf_line[buf_end] != '\n' && buf_line[buf_end])
		buf_end++;
	// 3.5 - Décaler encore buf_end si on a arrêté la boucle à \n
	if (buf_line[buf_end] == '\n')
		buf_end++;
	// 3.6 - Initialiser line avec malloc de la taille de buf_end + 1
	line = malloc((buf_end + 1) * sizeof(char));
	// 3.7 - Contrôle du malloc sur line
	if (!line)
		return (NULL);
	// 3.8 - Boucle pour mettre buf_line dans line jusqu'à buf_end
	while (i < buf_end)
	{
		line[i] = buf_line[i];
		i++;
	}
	// 3.9 - Rajouter le \0 à la fin de line
	line[i] = '\0';
	// 3.10 - Retourner line (la ligne à afficher)
	return (line);
}

// 4 - Fonction offset_buf_line qui prend en paramètre un char * correspondant à buf_line
// et renvoie une sous-chaine de buf_line qui commence après le premier caractère \n rencontré dans buf_line.
// Dans get_next_line, buf_line devient cette nouvelle sous-chaîne
char	*offset_buf_line(char	*buf_line)
{
	// 4.1 - On définit 3 variables : 1 char * correspondant à la nouvelle buf_line,
	// 1 int pour l'index du début de la nouvelle buf_line et 1 int pour l'index
	char	*new_bline;
	int		start;
	int		i;

	// 4.2 - On initialise les 2 int à 0
	start = 0;
	i = 0;
	// 4.3 - Contrôle retourner NULL si buf_line est NULL
	if (!buf_line)
		return (NULL);
	// 4.4 - Boucle while pour décaler l'index de début tant qu'on ne rencontre pas de \n ou \0
	while (buf_line[start] != '\n' && buf_line[start])
		start++;
	// 4.5 - if pour décaler l'index de début si on s'était arrêté à un \n
	if (buf_line[start] == '\n')
		start++;
	// 4.6 - Initialisation de la nouvelle char avec malloc de la taille de buf_line - start + 1
	new_bline = malloc((ft_strlen(buf_line) - start + 1) * sizeof(char));
	// 4.7 - Contrôle du malloc
	if (!new_bline)
		return (NULL);
	// 4.8 - Boucle while pour mettre buf_line dans la nouvelle char * à partir de start
	while (buf_line[start + i])
	{
		new_bline[i] = buf_line[start + i];
		i++;
	}
	// 4.9 - Libérer l'ancienne buf_line
	free (buf_line);
	// 4.10 - Rajouter le caractère nul à la fin de la nouvelle buf_line
	new_bline[i] = '\0';
	// 4.11 - Retourner la nouvelle buf_line
	return (new_bline);
}

/*
#include <stdio.h>
int main()
{
	int	fd = open("text.txt", O_RDONLY);
	printf("1: %s", get_next_line(fd));
	printf("2: %s", get_next_line(fd));
	printf("3: %s", get_next_line(fd));
	printf("4: %s", get_next_line(fd));
	printf("5: %s", get_next_line(fd));
	printf("6: %s", get_next_line(fd));
	printf("7: %s", get_next_line(fd));
	printf("8: %s", get_next_line(fd));
	printf("9: %s", get_next_line(fd));
	printf("10: %s", get_next_line(fd));
	printf("11: %s", get_next_line(fd));
	printf("12: %s", get_next_line(fd));
	close(fd);
}
*/