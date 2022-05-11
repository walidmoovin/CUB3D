/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:55:56 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 10:54:35 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	file_lines(char *str)
{
	int		i;
	int		fd;
	char	*gnl;

	fd = open(str, O_RDONLY);
	gnl = ft_strdup("");
	i = 1;
	while (gnl)
	{
		if (gnl)
			free(gnl);
		gnl = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

void	map_info(char **file, t_data *data)
{
	int	s;
	int	i;

	s = 0;
	i = -1;
	while (file[++i])
	{
		if (map_line(file[i]) && ft_strcmp(file[i], "\n"))
			s = 1;
		if (s == 1)
		{
			if (ft_strlen(file[i]) > data->parsing.map_maxlen)
				data->parsing.map_maxlen = ft_strlen(file[i]);
			data->parsing.map_lines++;
		}
	}
}

int	valid_colors(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->parsing.floor[++y])
	{
		x = -1;
		while (data->parsing.floor[y][++x])
			if (!ft_isdigit(data->parsing.floor[y][x]) || y > 2 \
			|| ft_atoi(data->parsing.floor[y]) > 255 \
			|| ft_atoi(data->parsing.floor[y]) < 0)
				return (0);
	}
	y = -1;
	while (data->parsing.ceiling[++y])
	{
		x = -1;
		while (data->parsing.ceiling[y][++x])
			if (!ft_isdigit(data->parsing.ceiling[y][x]) || y > 2 \
				|| ft_atoi(data->parsing.ceiling[y]) > 255
				|| ft_atoi(data->parsing.ceiling[y]) < 0)
				return (0);
	}
	return (1);
}

void	char_to_int(t_data *data)
{
	int	i;
	int	y;

	data->map = malloc(sizeof(int *) * data->parsing.map_lines);
	i = -1;
	while (data->parsing.map[++i])
	{
		y = -1;
		data->map[i] = malloc(sizeof(int) * data->parsing.map_maxlen);
		while (data->parsing.map[i][++y])
		{
			if (data->parsing.map[i][y] == 'N' || data->parsing.map[i][y] == 'S'
				|| data->parsing.map[i][y] == 'E' \
				|| data->parsing.map[i][y] == 'W')
			{
				player_dir(data->parsing.map[i][y], data);
				data->map[i][y] = 3;
			}
			else
				data->map[i][y] = data->parsing.map[i][y] - '0';
		}
	}
}

void	player_dir(char dir, t_data *data)
{
	if (dir == 'N' || dir == 'S')
	{
		data->rayc.player_dirx = 0;
		data->rayc.player_diry = -1;
		data->rayc.planex = 0.66;
		data->rayc.planey = 0;
	}
	if (dir == 'S')
	{
		data->rayc.player_diry *= -1;
		data->rayc.planex *= -1;
	}
	if (dir == 'E' || dir == 'W')
	{
		data->rayc.player_dirx = 1;
		data->rayc.player_diry = 0;
		data->rayc.planex = 0.0;
		data->rayc.planey = 0.66;
	}
	if (dir == 'W')
	{
		data->rayc.player_dirx *= -1;
		data->rayc.planey *= -1;
	}
}
