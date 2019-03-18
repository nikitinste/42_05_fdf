/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:08:08 by uhand             #+#    #+#             */
/*   Updated: 2019/03/18 17:34:41 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_persp_cood(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd)
{
	if (mlx && v && crd)
		return ;
}

void	get_magic(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd, \
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
	crd->x[i->x][i->y] = v->x + i->x_crd;
	crd->y[i->x][i->y] = v->y + i->y_crd;
	if (mlx->img->far_prm == 1)
		crd->far[i->x][i->y] = i->z_crd;
}

void	set_z_limits(t_mlx_prms *mlx, t_view_prms *v)
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

void	set_high_color(t_mlx_prms *mlx, t_draw_image *draw, int prm)
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
