/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileverif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:25:17 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 11:28:54 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fileverif(char *str)
{
	int	i;
	int	fd;

	i = ft_strlen(str);
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || \
	str[i - 4] != '.')
		return (0);
	fd = open(str, O_DIRECTORY | O_RDONLY);
	if (fd != -1)
		return (0);
	close (fd);
	return (1);
}

int	fileverif2(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!txt_line(str[i], 'N', 'O')
			&& !txt_line(str[i], 'S', 'O')
			&& !txt_line(str[i], 'W', 'E')
			&& !txt_line(str[i], 'E', 'A')
			&& !txt_line(str[i], 'F', ' ')
			&& !txt_line(str[i], 'C', ' ') && !map_line(str[i])
			&& !only_sp(str[i]) && str[i][0] != '\n')
			return (0);
	}
	i = -1;
	while (str[++i])
	{
		if (map_line(str[i]))
			return (1);
	}
	return (0);
}

int	wall_algo(int i, int y, t_data *data)
{
	if (data->parsing.map[i][y + 1] == ' ' \
	|| data->parsing.map[i][y - 1] == ' ')
		return (0);
	if (i && i != data->parsing.map_lines - 1)
		if (data->parsing.map[i + 1][y] == ' ' \
		|| data->parsing.map[i - 1][y] == ' ')
			return (0);
	if (ft_strchr(data->parsing.map[0], '0')
		|| ft_strchr(data->parsing.map[data->parsing.map_lines - 1], '0'))
		return (0);
	return (1);
}

int	verifmap(t_data *data)
{
	static int	i = -1;
	int			y;

	while (data->parsing.map[++i])
	{
		if (only_sp(data->parsing.map[i]) || data->parsing.map[i][0] == '0'
			|| data->parsing.map[i][data->parsing.map_maxlen - 1] == '0')
			return (0);
		y = -1;
		while (data->parsing.map[i][++y])
		{
			if (!map_char(data->parsing.map[i][y]))
				return (0);
			else if (is_direction(data->parsing.map[i][y]))
			{
				data->rayc.player_posy = i + 0.5;
				data->rayc.player_posx = y + 0.5;
				data->parsing.player++;
			}
			else if (data->parsing.map[i][y] == '0' && !wall_algo(i, y, data))
				return (0);
		}
	}
	return (1);
}

int	is_direction(char c)
{
	if (c == 'N' || c == 'W' \
		|| c == 'S' || c == 'E')
		return (1);
	return (0);
}
