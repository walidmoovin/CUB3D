/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileverif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:25:17 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:00 by wbekkal          ###   ########.fr       */
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
			&& !txt_linec(str[i], 'F', ' ')
			&& !txt_linec(str[i], 'C', ' ')
			&& !map_line(str[i])
			&& str[i][0] != '\n')
			return (0);
	}
	return (1);
}

int	verifmap(t_data *data)
{
	static int	i = -1;
	int			y;

	while (data->parsing.map[++i])
	{
		y = -1;
		while (data->parsing.map[i][++y])
		{
			if (is_direction(data->parsing.map[i][y]))
			{
				data->rayc.player_posy = i + 0.5;
				data->rayc.player_posx = y + 0.5;
				data->parsing.player++;
				player_dir(data->parsing.map[i][y], data);
				if (wall_algo(data, y, i))
					return (0);
			}
		}
	}
	return (1);
}

int	wall_algo(t_data *data, int x, int y)
{
	static char	*verif;
	int			tmp;

	tmp = data->parsing.map_maxlen - 1;
	if (x < 0 || x >= tmp || y < 0 || y >= data->parsing.map_lines)
		return (1);
	if (!verif)
		verif = ft_calloc(data->parsing.map_lines * tmp + 1, sizeof(char));
	if (verif[y * tmp + x])
		return (0);
	verif[y * tmp + x] = 1;
	if (data->parsing.map[y][x] == '1')
		return (0);
	else if (wall_algo(data, x + 1, y) || wall_algo(data, x - 1, y) \
		|| wall_algo(data, x, y + 1) || wall_algo(data, x, y - 1))
		return (1);
	else
		return (0);
}

int	is_direction(char c)
{
	if (c == 'N' || c == 'W' || c == 'S' || c == 'E')
		return (1);
	return (0);
}
