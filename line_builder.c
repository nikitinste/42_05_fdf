/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:18:06 by uhand             #+#    #+#             */
/*   Updated: 2019/02/18 19:05:03 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void			put_pix_to_img(t_img_data img, int x, int y, int color)
{
	int	*image;

	if (x < 0 || y < 0 || x >= img.win->x || y >= img.win->y)
		return ;
	image = (int*)img.addr;
	image[(y * (img.lsz / 4)) + x] = color;
}

int	get_grad_color(t_img_data *img, t_grad_prms *clr, int pos)
{
	int				start;
	t_grad			grad;

	if (clr->a == clr->b || pos == 0)
		return (clr->a);
	if (img->ndn == 0)
		start = 0;
	else
		start = 1;
	grad.a = (unsigned char*)&clr->a;
	grad.b = (unsigned char*)&clr->b;
	grad.d1 = (int)grad.b[start] - (int)grad.a[start];
	grad.d2 = (int)grad.b[start + 1] - (int)grad.a[start + 1];
	grad.d3 = (int)grad.b[start + 2] - (int)grad.a[start + 2];
	grad.color = 0;
	grad.c = (unsigned char*)&grad.color;
	grad.c[start] = ((grad.d1 * pos) / clr->delta) + grad.a[start];
	grad.c[start + 1] = ((grad.d2 * pos) / clr->delta) + grad.a[start + 1];
	grad.c[start + 2] = ((grad.d3 * pos) / clr->delta) + grad.a[start + 2];
	return (grad.color);
}

static void		get_delta(t_pix_prm *a, t_pix_prm *b, t_line_prm *l)
{
	l->d_ind = 0;
	l->dx = b->x - a->x;
	l->dy = b->y - a->y;
	if (ft_abs(l->dx) > ft_abs(l->dy))
	{
		l->d_big = l->dx;
		l->d_small = l->dy;
		l->d_ind = 1;
	}
	else
	{
		l->d_big = l->dy;
		l->d_small = l->dx;
	}
	if (l->d_big < 0)
		l->sign = -1;
	else
		l->sign = 1;
}

static int		get_coord(t_line_prm *l)
{
	int				coord;

	if (l->i == ft_abs(l->d_big))
		return (l->d_small);
	coord = ((l->d_small * l->i) / ft_abs(l->d_big));
	return (coord);
}

void			put_line_to_img(t_img_data img, t_pix_prm a, t_pix_prm b)
{
	t_line_prm		l;
	t_grad_prms		clr;

	get_delta(&a, &b, &l);
	clr.delta = ft_abs(l.d_big);
	clr.a = a.color;
	clr.b = b.color;
	l.i = 0;
	while (l.i <= ft_abs(l.d_big))
	{
		if (l.d_ind == 1)
			put_pix_to_img(img, (a.x + (l.i * l.sign)), (a.y + get_coord(&l)), \
				get_grad_color(&img, &clr, l.i));
		else
			put_pix_to_img(img, (a.x + get_coord(&l)), (a.y + (l.i * l.sign)), \
				get_grad_color(&img, &clr, l.i));
		l.i++;
	}
}
