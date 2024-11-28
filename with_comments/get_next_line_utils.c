/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qliso <qliso@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:22:50 by qliso             #+#    #+#             */
/*   Updated: 2024/11/21 20:22:54 by qliso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// 1 - Fonction taille de la chaine (strlen) qui prend un paramètre const char* et renvoie un size_t
size_t	ft_strlen(const char *s)
{
	// 1.1 - On définit une variable int correspondant à la longueur de la chaine de caractères
	int	len;

	// 1.2 - On initialise cette variable
	len = 0;
	// 1.3 - Boucle sur la chaîne de caractères
	while (s[len])
		len++;
	// 1.4 - On retourne la variable int
	return (len);
}

// 2 - Fonction strdup qui prend un paramètre const char* et renvoie un pointeur char *
// sur une chaine dont les caractères sont les mêmes que le paramètre
char	*ft_strdup(const char *s)
{
	// 2.1 - On définit 2 variables : 1 char * correspondant à la nouvelle str et 1 int comme index
	char	*dest;
	int		i;

	// 2.2 - On initialise l'index
	i = 0;
	// 2.3 - On initialise la nouvelle char * avec un malloc de la taille de s + 1 et on protège le malloc avec if(NULL)
	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dest)
		return (NULL);
	// 2.4 - On boucle sur la char* en paramètres avec l'index pour mettre les valeurs dans la nouvelle chaîne
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	// 2.5 - On n'oublie pas le caractère nul à la fin de la nouvelle chaîne
	dest[i] = '\0';
	// 2.6 - On retourne la nouvelle chaîne
	return (dest);
}

// 3 - Fonction strjoin qui prend deux paramètres const char * et renvoie un pointeur char*
// sur une autre chaîne qui concatène les deux paramètres
char	*ft_strjoin(char const *s1, char const *s2)
{
	// 3.1 - On définit 3 variables : 2 int qui servent d'index, 1 pour parcourir s1 et s2 et 1 pour dest
	// et 1 char * correspondant à la nouvelle chaine de caractères
	int		i;
	int		j;
	char	*dest;

	// 3.2 - On initialise les deux index à 0
	i = 0;
	j = 0;
	// 3.3 - On initialise la nouvelle chaîne avec malloc de la taille des 2 chaines + 1 et on protège le malloc
	dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	// 3.4 - On parcourt s1 et on met chaque caractère dans dest
	while (s1[i])
		dest[j++] = s1[i++];
	// 3.5 - On réinitialise l'index qui parcourt s1 à 0
	i = 0;
	// 3.5 - On parcourt s2 et on met chaque caractère dans dest
	while (s2[i])
		dest[j++] = s2[i++];
	// 3.6 - On rajoute le caractère nul \0 à la fin de dest
	dest[j] = 0;
	// 3.7 - On free s1 en le castant en void car le paramètre appelé par la fonction est const
	free ((void *)(s1));
	// 3.8 - On retourne la nouvelle chaîne de caractères
	return (dest);
}

// 4 - Fonction strchr qui prend en paramètre un const char* et un int (que l'on castera en char dans la fonction)
// et renvoie un char* qui correspond au paramètre char* dès qu'on trouve dans ce paramètre le premier caractère
// égal au second paramètre
char	*ft_strchr(const char *s, int c)
{
	// 4.1 - On définit 2 variables : un unsigned int qui sert d'index et un char qui sert à cast le 2ème paramètre c
	unsigned int	i;
	char			c_char;

	// 4.2 - On initialise l'index à 0 et on cast le paramètre int dans la variable char
	i = 0;
	c_char = (char) c;
	// 4.3 - On boucle sur la chaîne de caractères en paramètre
	while (s[i])
	{
		// 4.4 - Dès qu'on rencontre le caractère, on retourne l'adresse de l'emplacement dans la chaîne de caractères
		// en castant en char * car s est const
		if (s[i] == c_char)
			return ((char *) &s[i]);
		i++;
	}
	// 4.5 - On refait le check en sortie de boucle au cas où on cherchait le caractère nul pour retourner une chaîne vide
	if (s[i] == c_char)
		return ((char *) &s[i]);
	// 4.6 - On retourne NULL si aucun des checks n'a été satisfait.
	return (NULL);
}
