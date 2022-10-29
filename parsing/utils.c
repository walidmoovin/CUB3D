/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:23:02 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:17 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, char c)
{
	if (!s)
		return (0);
	while (*s++)
		if (*s == c)
			return (1);
	return (0);
}

int	free_return(char **tab, char **tab2)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
	i = -1;
	if (tab2)
	{
		while (tab2[++i])
			free(tab2[i]);
		free(tab2);
	}
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}

int	map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N'
		|| c == 'E' || c == 'S' || c == 'W' || c == '\n' || c == ' ')
		return (1);
	return (0);
}
