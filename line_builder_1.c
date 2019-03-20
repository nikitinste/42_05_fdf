/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_builder_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 13:43:52 by uhand             #+#    #+#             */
/*   Updated: 2019/03/20 20:55:44 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		put_pix_to_img(t_line_prm *l, int x, int y, int color)
{
	int	*image;

	if (x < 0 || y < 0 || x >= l->img->win->x || y >= l->img->win->y)
		return (0);
	image = (int*)l->img->addr;
	if (l->img->b_clr == color)
		color = get_invers_clr(color, l->img->ndn);
	image[(y * (l->img->lsz / 4)) + x] = color;
	return (0);
}

void	set_grad_color(t_grad *g, t_grad_prms *clr, int pos)
{
	g->a = (unsigned char*)&clr->a;
	g->b = (unsigned char*)&clr->b;
	g->d_alpha = (int)g->b[g->alpha] - (int)g->a[g->alpha];
	g->d1 = (int)g->b[g->start] - (int)g->a[g->start];
	g->d2 = (int)g->b[g->start + 1] - (int)g->a[g->start + 1];
	g->d3 = (int)g->b[g->start + 2] - (int)g->a[g->start + 2];
	g->color = 0;
	g->c = (unsigned char*)&(g->color);
	g->c[g->start] = ((g->d1 * pos) / clr->delta) + g->a[g->start];
	g->c[g->start + 1] = ((g->d2 * pos) / clr->delta) + g->a[g->start + 1];
	g->c[g->start + 2] = ((g->d3 * pos) / clr->delta) + g->a[g->start + 2];
	g->c[g->alpha] = ((g->d_alpha * pos) / clr->delta) + g->a[g->alpha];
}

void	persp_coord_recursive(t_mlx_prms *mlx, int *rec_counter)
{
	if (*rec_counter == 0)
	{
		*rec_counter = *rec_counter + 1;
		mouse_scale(4, mlx);
		draw_image(mlx, mlx->v, mlx->map, mlx->color);
		return ;
	}
	if (*rec_counter == 1)
	{
		*rec_counter = *rec_counter - 1;
		mlx->v->proj = 0;
		draw_image(mlx, mlx->v, mlx->map, mlx->color);
	}
}
