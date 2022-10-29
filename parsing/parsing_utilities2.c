/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utilities2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:55:56 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:07 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	file_lines(char *str)
{
	int		i;
	int		fd;
	char	*gnl;

	fd = open(str, O_RDONLY);
	gnl = get_next_line(fd);
	i = 0;
	while (gnl)
	{
		i++;
		if (gnl)
			free(gnl);
		gnl = get_next_line(fd);
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
			if (y > 2 || (!ft_isdigit(data->parsing.floor[y][x])
				&& data->parsing.floor[y][x] != ' ')
				|| ft_atoi(data->parsing.floor[y]) > 255
				|| ft_atoi(data->parsing.floor[y]) < 0)
				return (0);
	}
	if (!verif_color_utils(data))
		return (0);
	return (1);
}

int	verif_color_utils(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->parsing.ceiling[++y])
	{
		x = -1;
		while (data->parsing.ceiling[y][++x])
			if (y > 2 || (!ft_isdigit(data->parsing.ceiling[y][x])
				&& data->parsing.ceiling[y][x] != ' ')
				|| ft_atoi(data->parsing.ceiling[y]) > 255
				|| ft_atoi(data->parsing.ceiling[y]) < 0)
				return (0);
	}
	return (1);
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
