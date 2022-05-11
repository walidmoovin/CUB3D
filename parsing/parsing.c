/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:57:03 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 13:36:50 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	core_parsing(t_data *data, char **argv)
{
	char	**file;
	int		i;

	if (!fileverif(argv[1]))
		return (0);
	file = parse_file(argv[1]);
	if (!file || !fileverif2(file))
		return (0);
	map_info(file, data);
	parse_map(file, data);
	if (!verifmap(data) || data->parsing.player != 1)
		return (0);
	parse_txt(file, data);
	if (data->parsing.count_error != 6 || !valid_colors(data))
		return (0);
	char_to_int(data);
	i = 0;
	while (data->parsing.map[i])
		free(data->parsing.map[i++]);
	free(data->parsing.map);
	i = 0;
	while (file[i])
		free(file[i++]);
	free(file);
	return (1);
}

char	**parse_file(char *argv)
{
	char	**str;
	int		fd;
	int		i;

	i = file_lines(argv);
	str = malloc(sizeof(char *) * (i + 1));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = 0;
	while (1)
	{
		str[i] = get_next_line(fd);
		if (str[i] == NULL)
			break ;
		i++;
	}
	str[i] = NULL;
	if (!map_line(str[i - 1]) || only_sp(str[i - 1]) || str[i - 1][0] == '\n')
		return (NULL);
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
		if (map_line(str[i]) && ft_strcmp(str[i], "\n"))
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
				data->parsing.map[y][s++] = ' ';
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
		if (txt_line(str[i], 'N', 'O'))
			data->parsing.no_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_line(str[i], 'S', 'O'))
			data->parsing.so_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_line(str[i], 'W', 'E'))
			data->parsing.we_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_line(str[i], 'E', 'A'))
			data->parsing.ea_txt = get_txt(ft_strdup(str[i]), data);
		else if (txt_line(str[i], 'F', ' '))
			data->parsing.floor = get_color(ft_split(str[i], ','), data);
		else if (txt_line(str[i], 'C', ' '))
			data->parsing.ceiling = get_color(ft_split(str[i], ','), data);
	}
}
