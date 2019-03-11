/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:08:08 by uhand             #+#    #+#             */
/*   Updated: 2019/03/10 20:09:31 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void get_persp_cood(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd)
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
	i->y_crd = - i->x_cr * sin(OZ) + i->y_cr * cos(OZ);
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
