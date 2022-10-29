/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbekkal <wbekkal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:24:06 by wbekkal           #+#    #+#             */
/*   Updated: 2022/06/28 11:31:05 by wbekkal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_press(int keycode, t_data *data)
{
	if (keycode == KEY_ECHAP)
		safe_exit(data);
	if (keycode == KEY_W)
		data->keys.w = 1;
	if (keycode == KEY_S)
		data->keys.s = 1;
	if (keycode == KEY_D)
		data->keys.d = 1;
	if (keycode == KEY_A)
		data->keys.a = 1;
	if (keycode == ROTATE_LEFT)
		data->keys.rot_left = 1;
	if (keycode == ROTATE_RIGHT)
		data->keys.rot_right = 1;
	return (0);
}

int	ft_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	if (keycode == KEY_S)
		data->keys.s = 0;
	if (keycode == KEY_D)
		data->keys.d = 0;
	if (keycode == KEY_A)
		data->keys.a = 0;
	if (keycode == ROTATE_LEFT)
		data->keys.rot_left = 0;
	if (keycode == ROTATE_RIGHT)
		data->keys.rot_right = 0;
	return (0);
}

void	keys_loop(t_data *data)
{
	double	rotation;
	double	olddirx;
	double	oldplanex;

	strafe(data);
	move(data);
	rotation = M_PI / 200;
	if (data->keys.rot_left || data->keys.rot_right)
	{
		if (data->keys.rot_left)
			rotation *= -1;
		olddirx = data->rayc.player_dirx;
		data->rayc.player_dirx = data->rayc.player_dirx * cos(rotation) \
		- data->rayc.player_diry * sin(rotation);
		data->rayc.player_diry = olddirx * sin(rotation) \
		+ data->rayc.player_diry * cos(rotation);
		oldplanex = data->rayc.planex;
		data->rayc.planex = data->rayc.planex * cos(rotation) \
		- data->rayc.planey * sin(rotation);
		data->rayc.planey = oldplanex * sin(rotation) \
		+ data->rayc.planey * cos(rotation);
	}
}

void	strafe(t_data *data)
{
	int	s;

	s = 1;
	if (data->keys.a || data->keys.d)
	{
		if (data->keys.a)
			s *= -1;
		if (data->parsing.map[(int)(data->rayc.player_posy)][\
		(int)(data->rayc.player_posx + (data->rayc.planex * s * 0.1))] == '0')
			data->rayc.player_posx += data->rayc.planex * s * 0.1;
		if (data->parsing.map[(int)(data->rayc.player_posy + \
		(data->rayc.planey * s * 0.1))][(int)(data->rayc.player_posx)] == '0')
			data->rayc.player_posy += data->rayc.planey * s * 0.1;
	}
}

void	move(t_data *data)
{
	double	d;
	double	v;

	d = 1.0;
	v = 1.0;
	if (data->keys.w || data->keys.s)
	{
		if (data->keys.s)
			d *= -1.0;
		if (data->parsing.map[(int)(data->rayc.player_posy)][\
		(int)(data->rayc.player_posx + (data->rayc.player_dirx * v * d))] == '0'
		|| is_direction(data->parsing.map[(int)(data->rayc.player_posy)][\
		(int)(data->rayc.player_posx + (data->rayc.player_dirx * v * d))]))
			data->rayc.player_posx += (data->rayc.player_dirx * d * v) * 0.1;
		if (data->parsing.map[(int)(data->rayc.player_posy + \
		(data->rayc.player_diry * v * d))][(int)(data->rayc.player_posx)] == '0'
		|| is_direction(data->parsing.map[(int)(data->rayc.player_posy + \
		(data->rayc.player_diry * v * d))][(int)(data->rayc.player_posx)]))
			data->rayc.player_posy += (data->rayc.player_diry * d * v) * 0.1;
	}
}
