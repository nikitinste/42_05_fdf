/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:10:38 by uhand             #+#    #+#             */
/*   Updated: 2019/03/10 19:51:08 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_move(int x, int y, void *prm)
{
	static t_mouse_crd	scroll;
	static t_mouse_crd	mouse;
	t_mlx_prms			*mlx;

	mlx = (t_mlx_prms*)prm;
	if (mlx->v->scr_hold == 1)
		if (!mouse_scroll(mlx, &scroll, x, y))
			return (0);
	if (mlx->v->mouse_hld == 1)
		if (!mouse_button(mlx, &mouse, x, y))
			return (0);
	return (0);
}

int		mouse_release(int key, int x, int y, void *prm)
{
	t_mlx_prms	*mlx;

	mlx = (t_mlx_prms*)prm;
	if (x && y)
	{
		if (key == 3)
		{
			mlx->v->scr_hold = 0;
			mlx->scroll->i = 0;
		}
		if (key == 1)
		{
			mlx->v->mouse_hld = 0;
			mlx->mouse->i = 0;
		}
	}
	return (0);
}

int		mouse_press(int key, int x, int y, void *prm)
{
	t_mlx_prms	*mlx;

	mlx = (t_mlx_prms*)prm;
	if (x >= 0 && x < mlx->win->x && y >= 0 && y < mlx->win->y)
	{
		if (key == 5 || key == 4)
			mouse_scale(key, mlx);
		if (key == 3)
		{
			mlx->v->scr_hold = 1;
			return (0);
		}
		if (key == 1)
		{
			mlx->v->mouse_hld = 1;
			return (0);
		}
		renew_window(mlx);
	}
	return (0);
}

int		deal_key(int key, void *prm)
{
	t_mlx_prms	*x;

	x = (t_mlx_prms*)prm;
	if (key == 53)
	{
		ft_putnbr(key);
		mlx_destroy_window(x->mlx_ptr, x->win_ptr);
		exit(0);
	}
	if (key == 6 || key == 0 || key == 125 || key == 126 || key == 123 || \
		key == 124 || key == 17 || key == 3 || key == 37 || key == 34)
		map_rotation(key, x);
	if (key == 18)
	{
		if (x->img->woo_prm == 0)
			x->img->woo_prm = 1;
		else
			x->img->woo_prm = 0;
	}
	renew_window(x);
	return (0);
}
