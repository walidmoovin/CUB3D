/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:09:10 by wbekkal           #+#    #+#             */
/*   Updated: 2022/05/11 13:53:28 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	raycasting(t_data *data)
{	
	int		y;
	double	wallx;
	double	step;
	double	texpos;

	data->rayc.x = 0;
	while (data->rayc.x++ < WIDTH)
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
		if (data->rayc.drawstart < 0)
			data->rayc.drawstart = 0;
		data->rayc.drawend = data->rayc.lineheight / 2 + HEIGHT / 2;
		if (data->rayc.drawend >= HEIGHT)
			data->rayc.drawend = HEIGHT - 1;
		if (data->rayc.side == 0)
			wallx = data->rayc.player_posy + data->rayc.perpwalldist * data->rayc.raydiry;
		else
			wallx = data->rayc.player_posx + data->rayc.perpwalldist * data->rayc.raydirx;
		wallx -= floor(wallx);
		data->rayc.texx = (int)(wallx * (double)TEX_WIDTH);
		if (data->rayc.side == 0 && data->rayc.raydirx > 0)
			data->rayc.texx = TEX_WIDTH - data->rayc.texx - 1;
		if (data->rayc.side == 1 && data->rayc.raydiry < 0)
			data->rayc.texx = TEX_WIDTH - data->rayc.texx - 1;
		step = 1.0 * TEX_HEIGHT / data->rayc.lineheight;
		texpos = \
		(data->rayc.drawstart - HEIGHT / 2 + data->rayc.lineheight / 2) * step;
		y = data->rayc.drawstart - 1;
		while (++y < data->rayc.drawend)
		{
			data->rayc.texy = (int)texpos & (TEX_HEIGHT - 1);
			texpos += step;
			if (data->rayc.side == 1 && data->rayc.raydiry < 0)
				data->rayc.color = data->text.addr1[TEX_HEIGHT * data->rayc.texy + data->rayc.texx];
			if (data->rayc.side == 1 && data->rayc.raydiry >= 0)
				data->rayc.color = data->text.addr2[TEX_HEIGHT * data->rayc.texy + data->rayc.texx];
			if (data->rayc.side == 0 && data->rayc.raydirx < 0)
				data->rayc.color = data->text.addr3[TEX_HEIGHT * data->rayc.texy + data->rayc.texx];
			if (data->rayc.side == 0 && data->rayc.raydirx >= 0)
				data->rayc.color = data->text.addr4[TEX_HEIGHT * data->rayc.texy + data->rayc.texx];
			my_mlx_pixel_put(data, data->rayc.x, y, data->rayc.color);
		}
	}
}

void	init(t_data *data)
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
}

void	step_init(t_data *data)
{
	if (data->rayc.raydirx < 0)
	{
		data->rayc.stepx = -1;
		data->rayc.sidedistx = \
		(data->rayc.player_posx - data->rayc.mapx) * data->rayc.deltadistx;
	}
	else
	{
		data->rayc.stepx = 1;
		data->rayc.sidedistx = \
		(data->rayc.mapx + 1 - data->rayc.player_posx) * data->rayc.deltadistx;
	}
	if (data->rayc.raydiry < 0)
	{
		data->rayc.stepy = -1;
		data->rayc.sidedisty = \
		(data->rayc.player_posy - data->rayc.mapy) * data->rayc.deltadisty;
	}
	else
	{
		data->rayc.stepy = 1;
		data->rayc.sidedisty = \
		(data->rayc.mapy + 1 - data->rayc.player_posy) * data->rayc.deltadisty;
	}
}

void	dda(t_data *data)
{
	data->rayc.hit = 0;
	while (!data->rayc.hit)
	{
		if (data->rayc.sidedistx < data->rayc.sidedisty)
		{
			data->rayc.sidedistx += data->rayc.deltadistx;
			data->rayc.mapx += data->rayc.stepx;
			data->rayc.side = 0;
		}
		else
		{
			data->rayc.sidedisty += data->rayc.deltadisty;
			data->rayc.mapy += data->rayc.stepy;
			data->rayc.side = 1;
		}
		if (data->map[data->rayc.mapy][data->rayc.mapx] == 1)
			data->rayc.hit = 1;
	}
	if (data->rayc.side == 0)
		data->rayc.perpwalldist = \
		(data->rayc.sidedistx - data->rayc.deltadistx);
	else
		data->rayc.perpwalldist = \
		(data->rayc.sidedisty - data->rayc.deltadisty);
}
