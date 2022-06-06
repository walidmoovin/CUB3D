/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:31:09 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/02 11:39:12 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N'
		|| c == 'E' || c == 'S' || c == 'W' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	map_line(char *str)
{
	int	i;

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

char	*get_txt(char *str, t_data *data)
{
	int	i;

	while (*str != '.' && *str && *str != '/')
		str++;
	data->parsing.count_error++;
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
	while (!(*str[0] >= '0' && *str[0] <= '9') && *str[0])
		str[0]++;
	data->parsing.count_error++;
	return (str);
}
