/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:23:02 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 11:28:46 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

char	*ft_strjoin(char *parts, char *line)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!parts)
	{
		parts = malloc(sizeof(char));
		parts[0] = '\0';
	}
	if (!parts || !line)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(parts) + ft_strlen(line)) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (parts)
		while (parts[++i] != '\0')
			str[i] = parts[i];
	while (line[j] != '\0')
		str[i++] = line[j++];
	str[ft_strlen(parts) + ft_strlen(line)] = '\0';
	free(parts);
	return (str);
}

char	*fill_line(char *parts)
{
	int		i;
	char	*line;

	i = 0;
	if (!parts[i])
		return (NULL);
	while (parts[i] && parts[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (parts[i] && parts[i] != '\n')
	{
		line[i] = parts[i];
		i++;
	}
	if (parts[i] == '\n')
	{
		line[i] = parts[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_parts(char *parts)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (parts[i] && parts[i] != '\n')
		i++;
	if (!parts[i])
	{
		free(parts);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(parts) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (parts[i])
		str[j++] = parts[i++];
	str[j] = '\0';
	free(parts);
	return (str);
}
