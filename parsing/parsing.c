/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:57:03 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:50:10 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	core_parsing(t_data *data, char **argv)
{
	char	**file;

	if (!fileverif(argv[1]))
		return (0);
	file = parse_file(argv[1]);
	if (!file || !fileverif2(file) ||!verif_lot_map(file))
		return (free_return(file, data->parsing.map));
	map_info(file, data);
	parse_map(file, data);
	if (!verifmap(data) || data->parsing.player != 1)
		return (free_return(file, data->parsing.map));
	parse_txt(file, data);
	if (!verif_number_of_info(data) || !valid_colors(data))
		return (free_return(file, data->parsing.map));
	if (number_of_tables(data->parsing.ceiling) != 3 \
	|| number_of_tables(data->parsing.floor) != 3)
		return (0);
	free_tab(file);
	return (1);
}

int	verif_lot_map(char **str)
{
	int	i;
	int	e;

	e = 0;
	i = -1;
	while (str[++i])
	{
		if (map_line(str[i]) && e == 0)
			e = 1;
		if (e == 1)
		{
			if (!map_line(str[i]))
				return (0);
		}
	}
	return (1);
}

char	**parse_file(char *argv)
{
	char	**str;
	int		fd;
	int		i;

	i = file_lines(argv);
	if (!i)
		return (NULL);
	str = malloc(sizeof(char *) * (i + 1));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = 0;
	str[i] = get_next_line(fd);
	while (str[i])
	{
		i++;
		str[i] = get_next_line(fd);
	}
	str[i] = NULL;
	close (fd);
	return (str);
}

void	parse_map(char **str, t_data *data)
{
	static int		i = -1;
	static int		s = 1;
	static int		y = 0;

	data->parsing.map = malloc(sizeof(char *) * (data->parsing.map_lines + 1));
	while (str[++i])
	{
		if (map_line(str[i]))
			s = 0;
		if (!s)
		{
			data->parsing.map[y] = malloc(1 * (data->parsing.map_maxlen + 1));
			while (str[i][s] && str[i][s] != '\n')
			{
				data->parsing.map[y][s] = str[i][s];
				s++;
			}
			while (s < data->parsing.map_maxlen - 1)
				data->parsing.map[y][s++] = '0';
			data->parsing.map[y][s++] = '\n';
			data->parsing.map[y][s] = '\0';
			y++;
		}
	}
	data->parsing.map[y] = NULL;
}

void	parse_txt(char **str, t_data *data)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (txt_line(str[i], 'N', 'O') && !data->parsing.n_txt++)
			data->parsing.no_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_line(str[i], 'S', 'O') && !data->parsing.s_txt++)
			data->parsing.so_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_line(str[i], 'W', 'E') && !data->parsing.w_txt++)
			data->parsing.we_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_line(str[i], 'E', 'A') && !data->parsing.e_txt++)
			data->parsing.ea_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_linec(str[i], 'F', ' ') && !data->parsing.f++)
			data->parsing.floor = get_color(ft_split(str[i], ','), data);
		else if (txt_linec(str[i], 'C', ' ') && !data->parsing.c++)
			data->parsing.ceiling = get_color(ft_split(str[i], ','), data);
	}
}
