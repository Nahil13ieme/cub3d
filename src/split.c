/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-saut <tle-saut@student.42perpignan>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 11:50:26 by tle-saut          #+#    #+#             */
/*   Updated: 2025/06/12 15:34:47 by tle-saut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char **ft_free(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

// Fonction pour compter le nombre de mots séparés par le caractère 'c'
static size_t ft_countword(const char *str, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			count++;
		if (str[i] == c && str[i + 1] == c)
			count++;
		i++;
	}
	return (count);
}

// Fonction pour calculer la longueur du mot à partir de l'index 'i'
static size_t ft_lenword(const char *s, size_t i, char c)
{
	size_t len;

	len = 0;
	while (s[i + len] && s[i + len] != c)
		len++;
	return (len);
}

// Fonction qui extrait un mot de la chaîne en utilisant ft_substr
static char *ft_extract_word(const char *s, size_t start, size_t len)
{
	char *word;
	size_t i;

	i = 0;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	if (len == 0)
		return (" ");
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

// Fonction pour découper la chaîne en mots
char **ft_split_space(const char *s, char c)
{
	size_t i;
	size_t j;
	char **tab;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] && s[i + 1] == c)
			tab[j++] = ft_strdup(" ");
		if (s[i] == c)
			i++;
		else
		{
			if (ft_lenword(s, i, c) == 0)
				tab[j++] = ft_strdup(" ");
			tab[j] = ft_extract_word(s, i, ft_lenword(s, i, c));
			if (!tab[j++])
				return (ft_free(tab, j - 1));
			i = i + ft_lenword(s, i, c);
		}
	}
	tab[j] = NULL;
	return (tab);
}
