/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:48:23 by uhand             #+#    #+#             */
/*   Updated: 2019/03/20 11:25:35 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bump_up(double *angle, int *i, int a)
{
	*i = *i + a;
	if (*i >= 360)
		*i = *i - 360;
	*angle = (M_PI * *i) / 180;
}

void	bump_down(double *angle, int *i, int a)
{
	if (*i >= 0)
		*i = *i - a;
	if (*i < 0)
		*i = 360 + *i;
	*angle = (M_PI * *i) / 180;
}

void	left_iso(int key, t_mlx_prms *x)
{
	if (key == 37)
	{
		x->x_i = 270;
		x->y_i = 270;
		x->z_i = 0;
		x->v->x_ang = (M_PI * x->x_i) / 180;
		x->v->y_ang = (M_PI * x->y_i) / 180;
		x->v->z_ang = 0;
	}
	if (key == 34)
	{
		x->x_i = 315;
		x->y_i = 0;
		x->z_i = 45;
		x->v->x_ang = (M_PI * x->x_i) / 180;
		x->v->y_ang = 0;
		x->v->z_ang = (M_PI * x->z_i) / 180;
	}
}

void	top_front(int key, t_mlx_prms *x)
{
	if (key == 17)
	{
		x->v->x_ang = 0;
		x->v->y_ang = 0;
		x->v->z_ang = 0;
		x->x_i = 0;
		x->y_i = 0;
		x->z_i = 0;
	}
	if (key == 3)
	{
		x->x_i = 270;
		x->y_i = 0;
		x->z_i = 0;
		x->v->x_ang = (M_PI * x->x_i) / 180;
		x->v->y_ang = 0;
		x->v->z_ang = 0;
	}
}

void	map_rotation(int key, t_mlx_prms *x)
{
	if (key == 125)
		bump_up(&(x->v->x_ang), &(x->x_i), 5);
	if (key == 126)
		bump_down(&(x->v->x_ang), &(x->x_i), 5);
	if (key == 123)
		bump_up(&(x->v->y_ang), &(x->y_i), 5);
	if (key == 124)
		bump_down(&(x->v->y_ang), &(x->y_i), 5);
	if (key == 2)
		bump_up(&(x->v->z_ang), &(x->z_i), 5);
	if (key == 0)
		bump_down(&(x->v->z_ang), &(x->z_i), 5);
	if (key == 17 || key == 3)
		top_front(key, x);
	if (key == 37 || key == 34)
		left_iso(key, x);
}
