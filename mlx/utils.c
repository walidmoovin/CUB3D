/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:20 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:28:47 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = data->addr + (y * data->size_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	my_mlx_pixel_put2(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = data->addr2 + (y * data->size_l + x * (data->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	safe_exit(t_data *data)
{
	mlx_destroy_window(data->mlx_id, data->win_id);
	exit(0);
	return (1);
}

void	init_datas(t_data *data)
{
	data->rayc.camerax = 2 * data->rayc.x / (double)WIDTH - 1;
	data->rayc.raydirx = \
	data->rayc.player_dirx + data->rayc.planex * data->rayc.camerax;
	data->rayc.raydiry = \
	data->rayc.player_diry + data->rayc.planey * data->rayc.camerax;
	data->rayc.mapx = (int)data->rayc.player_posx;
	data->rayc.mapy = (int)data->rayc.player_posy;
	if (data->rayc.raydirx == 0)
		data->rayc.deltadistx = 1e30;
	else
		data->rayc.deltadistx = fabs(1 / data->rayc.raydirx);
	if (data->rayc.raydiry == 0)
		data->rayc.deltadisty = 1e30;
	else
		data->rayc.deltadisty = fabs(1 / data->rayc.raydiry);
	step_init(data);
	dda(data);
	data->rayc.lineheight = (int)(HEIGHT / data->rayc.perpwalldist);
	data->rayc.drawstart = -data->rayc.lineheight / 2 + HEIGHT / 2;
}

int	number_of_tables(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
