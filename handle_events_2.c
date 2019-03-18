/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:41:03 by uhand             #+#    #+#             */
/*   Updated: 2019/03/18 15:39:20 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_scroll(t_mlx_prms *mlx, t_mouse_crd *scroll, int x, int y)
{
	if (mlx->v->scr_hold == 1 && scroll->i == 0)
	{
		scroll->i = 1;
		scroll->x = x;
		scroll->y = y;
		mlx->scroll = scroll;
		return (0);
	}
	if (mlx->v->scr_hold == 1 && scroll->i == 1)
	{
		mlx->v->x += (x - scroll->x);
		mlx->v->y += (y - scroll->y);
		scroll->x = x;
		scroll->y = y;
		renew_window(mlx);
	}
	return (0);
}

int		mouse_button(t_mlx_prms *mlx, t_mouse_crd *mouse, int x, int y)
{
	if (mlx->v->mouse_hld == 1 && mouse->i == 0)
	{
		mouse->i = 1;
		mouse->x = x;
		mouse->y = y;
		mlx->mouse = mouse;
		return (0);
	}
	if (mlx->v->mouse_hld == 1 && mouse->i == 1)
	{
		if ((x - mouse->x) > 0)
			bump_down(&(mlx->v->y_ang), &(mlx->y_i), 3);
		else if ((x - mouse->x) < 0)
			bump_up(&(mlx->v->y_ang), &(mlx->y_i), 3);
		if ((y - mouse->y) > 0)
			bump_up(&(mlx->v->x_ang), &(mlx->x_i), 3);
		else if ((y - mouse->y) < 0)
			bump_down(&(mlx->v->x_ang), &(mlx->x_i), 3);
		mouse->x = x;
		mouse->y = y;
		renew_window(mlx);
	}
	return (0);
}

void	mouse_scale(int key, t_mlx_prms *mlx)
{
	if (key == 5)
	{
		if (mlx->v->scale >= 50)
		{
			if (mlx->v->scale < (mlx->v->scl_max - 5))
				mlx->v->scale += 5;
		}
		else if (mlx->v->scale < mlx->v->scl_max)
			mlx->v->scale++;
	}
	if (key == 4)
	{
		if (mlx->v->scale > 50)
			mlx->v->scale -= 5;
		else if (mlx->v->scale > 2)
			mlx->v->scale--;
	}
	if (key == 29)
	{
		set_scale(mlx, mlx->v);
		mlx->v->x = mlx->win->x / 2;
		mlx->v->y = mlx->win->y / 2;
	}
}

void	change_background(int key, t_mlx_prms *x)
{
	if (key == 43)
	{
		if ((BC - 0x080808) >= 0)
		{
			if (BC >= 0x505050 && (BC - 0x080808) < 0x505050)
				x->v->line_clr = get_invers_clr(x->v->line_clr, x->img->ndn);
			BC -= 0x080808;
		}
	}
	if (key == 47)
	{
		if ((BC + 0x080808) <= 0xFFFFFF)
		{
			if (BC < 0x505050 && (BC + 0x080808) >= 0x505050)
				x->v->line_clr = get_invers_clr(x->v->line_clr, x->img->ndn);
			BC += 0x080808;
		}
	}
}
