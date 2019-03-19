/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:08:08 by uhand             #+#    #+#             */
/*   Updated: 2019/03/19 19:08:30 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int	get_persp_cood(t_view_prms *v, t_coords *crd, t_coord_map *i)
{
	double		x_alpha;
	double		y_alpha;
	int			x_prev;
	int			y_prev;

	x_prev = i->x_crd;
	y_prev = i->y_crd;
	x_alpha = atan((double)i->x_crd / (double)(v->far - crd->far[i->x][i->y]));
	y_alpha = atan((double)i->y_crd / (double)(v->far - crd->far[i->x][i->y]));
	i->x_crd = (int)(v->far * tan(x_alpha));
	i->y_crd = (int)(v->far * tan(y_alpha));
	if (((i->x_crd > 0 && x_prev < 0) || (i->x_crd < 0 && x_prev > 0)) || \
		((i->y_crd > 0 && y_prev < 0) || (i->y_crd < 0 && y_prev > 0)))
		return (0);
	return (1);
}

int			get_magic(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd, \
	t_coord_map *i)
{
	i->x_cr = (i->y * SCL) - (((mlx->m->y - 1) * SCL) / 2);
	i->y_cr = (i->x * SCL) - (((mlx->m->x - 1) * SCL) / 2);
	i->z_cr = mlx->map[0][i->x][i->y] * SCL;
	i->x_crd = i->x_cr * cos(OZ) + i->y_cr * sin(OZ);
	i->y_crd = -i->x_cr * sin(OZ) + i->y_cr * cos(OZ);
	i->x_cr = i->x_crd;
	i->y_cr = i->y_crd;
	i->y_crd = i->y_cr * cos(OX) + i->z_cr * sin(OX);
	i->z_crd = i->z_cr * cos(OX) - i->y_cr * sin(OX);
	i->y_cr = i->y_crd;
	i->z_cr = i->z_crd;
	i->x_crd = i->x_cr * cos(OY) - i->z_cr * sin(OY);
	i->z_crd = i->x_cr * sin(OY) + i->z_cr * cos(OY);
	if (v->proj == 1 || mlx->img->far_prm == 1)
		crd->far[i->x][i->y] = i->z_crd;
	if (mlx->img->far_prm == 1 && i->z_crd < v->far_max)
		v->far_max = i->z_crd;
	if (mlx->img->far_prm == 1 && i->z_crd > v->far_min)
		v->far_min = i->z_crd;
	if (v->proj == 1)
		if (!get_persp_cood(v, crd, i))
			return (0);
	crd->x[i->x][i->y] = v->x + i->x_crd;
	crd->y[i->x][i->y] = v->y + i->y_crd;
	return (1);
}

void		set_z_limits(t_mlx_prms *mlx, t_view_prms *v)
{
	int		x;
	int		y;

	v->z_min = 0;
	v->z_max = 0;
	x = 0;
	while (x < mlx->m->x)
	{
		y = 0;
		while (y < mlx->m->y)
		{
			if (mlx->map[0][x][y] > v->z_max)
				v->z_max = mlx->map[0][x][y];
			if (mlx->map[0][x][y] < v->z_min)
				v->z_min = mlx->map[0][x][y];
			y++;
		}
		x++;
	}
	v->z_delta = v->z_max - v->z_min;
}

void		set_high_color(t_mlx_prms *mlx, t_draw_image *draw, int prm)
{
	t_grad_prms	clr;
	int			a_pos;
	int			b_pos;

	clr.a = LOWCLR;
	clr.b = HICLR;
	clr.delta = mlx->v->z_delta;
	a_pos = mlx->map[0][draw->x][draw->y] - mlx->v->z_min;
	if (prm == 1)
		b_pos = mlx->map[0][draw->x + 1][draw->y] - mlx->v->z_min;
	if (prm == 0)
		b_pos = mlx->map[0][draw->x][draw->y + 1] - mlx->v->z_min;
	draw->a.color = get_grad_color(mlx->img, &clr, a_pos);
	draw->b.color = get_grad_color(mlx->img, &clr, b_pos);
}

void		check_far_param(t_mlx_prms *mlx, t_coords *crd, \
	t_draw_image *draw, int prm)
{
	int			alpha;
	int			a_pos;
	int			b_pos;

	if (mlx->img->far_prm == 0)
		return ;
	a_pos = crd->far[draw->x][draw->y] - mlx->v->far_min;
	if (prm == 1)
		b_pos = crd->far[draw->x + 1][draw->y] - mlx->v->far_min;
	if (prm == 0)
		b_pos = crd->far[draw->x][draw->y + 1] - mlx->v->far_min;
	alpha = (a_pos * 255) / mlx->v->far_delta;
	set_alpha(mlx, &(draw->a.color), alpha);
	alpha = (b_pos * 255) / mlx->v->far_delta;
	set_alpha(mlx, &(draw->b.color), alpha);
}
