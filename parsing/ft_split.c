/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:32:36 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/23 18:51:15 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_words(char *str, char sep)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (str[i])
	{
		if ((!str[i + 1] || str[i + 1] == sep) && str[i] && str[i] != sep)
			y++;
		i++;
	}
	return (y);
}

void	write_in(char *from, char *dest, char sep)
{
	int	i;

	i = 0;
	while (from[i] && from[i] != sep)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static int	write_split(char *str, char **split, char separator)
{
	int	i;
	int	y;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] == separator)
			i++;
		else
		{
			y = 0;
			while (str[i + y] && str[i + y] != separator)
				y++;
			split[words] = malloc(sizeof(char) * (y + 1));
			if (!split[words])
				return (0);
			write_in(str + i, split[words], separator);
			words++;
			i += y;
		}
	}
	return (1);
}

char	**ft_split(char *str, char separator)
{
	char	**split;
	int		count;

	count = count_words(str, separator);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	split[count] = NULL;
	if (!write_split(str, split, separator))
		return (NULL);
	return (split);
}

int	only_sp(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}
