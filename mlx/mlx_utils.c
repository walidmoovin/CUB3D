/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:57:49 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/23 18:48:30 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	loop(t_data *data)
{
	keys_loop(data);
	memset(data->addr, 0xFF, HEIGHT * data->size_l);
	raycasting(data);
	mlx_put_image_to_window(data->mlx_id, data->win_id, data->img2, 0, 0);
	mlx_put_image_to_window(data->mlx_id, data->win_id, data->img, 0, 0);
	return (0);
}

void	draw_floor_ceiling(t_data *data)
{
	int	w;
	int	h;

	h = 0;
	while (h++ < (HEIGHT / 2))
	{
		w = 0;
		while (w++ < WIDTH)
			my_mlx_pixel_put2(data, w, h, \
			creatergb(ft_atoi(data->parsing.ceiling[0]), \
			ft_atoi(data->parsing.ceiling[1]), \
			ft_atoi(data->parsing.ceiling[2])));
	}
	while (h++ < HEIGHT)
	{
		w = 0;
		while (w++ < WIDTH)
			my_mlx_pixel_put2(data, w, h, \
			creatergb(ft_atoi(data->parsing.floor[0]), \
			ft_atoi(data->parsing.floor[1]), \
			ft_atoi(data->parsing.floor[2])));
	}
}

int	creatergb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	textures_parsing(t_data *data)
{
	if (!get_addr(data->parsing.no_txt, data) \
	|| !get_addr(data->parsing.so_txt, data) \
	|| !get_addr(data->parsing.we_txt, data) \
	|| !get_addr(data->parsing.ea_txt, data))
		return (0);
	data->text.add1 = (int *)mlx_get_data_addr(\
	get_addr(data->parsing.no_txt, data), &data->bpp, &data->size_l, &data->e);
	data->text.add2 = (int *)mlx_get_data_addr(\
	get_addr(data->parsing.so_txt, data), &data->bpp, &data->size_l, &data->e);
	data->text.add3 = (int *)mlx_get_data_addr(\
	get_addr(data->parsing.we_txt, data), &data->bpp, &data->size_l, &data->e);
	data->text.add4 = (int *)mlx_get_data_addr(\
	get_addr(data->parsing.ea_txt, data), &data->bpp, &data->size_l, &data->e);
	return (1);
}

void	*get_addr(char *text, t_data *data)
{
	void	*img;
	int		w;
	int		h;

	w = TEX_WIDTH;
	h = TEX_HEIGHT;
	img = mlx_xpm_file_to_image(data->mlx_id, text, &w, &h);
	if (!img)
		return (NULL);
	return (img);
}
