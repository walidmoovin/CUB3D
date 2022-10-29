/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:31:09 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:05 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_line(char *str)
{
	int	i;
	int	n;

	n = 0;
	i = -1;
	while (str[++i])
		if (str[i] != '\n' && str[i] != ' ')
			n = 1;
	if (n == 0)
		return (0);
	i = -1;
	while (str[++i])
		if (!map_char(str[i]))
			return (0);
	return (1);
}

int	txt_line(char *str, char first, char second)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == first && str[i + 1] == second && str[i + 2] == ' ')
		return (1);
	return (0);
}

int	txt_linec(char *str, char first, char second)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == first && str[i + 1] == second)
		return (1);
	return (0);
}

char	*get_txt(char *str, t_data *data)
{
	int	i;

	(void)data;
	while (*str != '.' && *str && *str != '/')
		str++;
	i = 0;
	while (*str != '\n' && *str)
	{
		str++;
		i++;
	}
	*str = '\0';
	while (i > 0)
	{
		str--;
		i--;
	}
	return (str);
}

char	**get_color(char **str, t_data *data)
{
	int	i;

	(void)data;
	i = -1;
	while (str[++i])
		while (!(*str[i] >= '0' && *str[i] <= '9') && *str[i])
			str[i]++;
	return (str);
}
