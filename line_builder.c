/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:18:06 by uhand             #+#    #+#             */
/*   Updated: 2019/03/09 15:36:04 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int				put_pix_to_img(t_line_prm *l, int x, int y, int color)
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

int				get_grad_color(t_img_data *img, t_grad_prms *clr, int pos)
{
	int				start;
	int				alpha;
	t_grad			grad;

	if (clr->a == clr->b || pos == 0)
		return (clr->a);
	if (img->ndn == 0)
	{
		start = 0;
		alpha = 3;
	}
	else
	{
		start = 1;
		alpha = 0;
	}
	grad.a = (unsigned char*)&clr->a;
	grad.b = (unsigned char*)&clr->b;
	grad.d_alpha = (int)grad.b[alpha] - (int)grad.a[alpha];
	grad.d1 = (int)grad.b[start] - (int)grad.a[start];
	grad.d2 = (int)grad.b[start + 1] - (int)grad.a[start + 1];
	grad.d3 = (int)grad.b[start + 2] - (int)grad.a[start + 2];
	grad.color = 0;
	grad.c = (unsigned char*)&grad.color;
	grad.c[start] = ((grad.d1 * pos) / clr->delta) + grad.a[start];
	grad.c[start + 1] = ((grad.d2 * pos) / clr->delta) + grad.a[start + 1];
	grad.c[start + 2] = ((grad.d3 * pos) / clr->delta) + grad.a[start + 2];
	grad.c[alpha] = ((grad.d_alpha * pos) / clr->delta) + grad.a[alpha];
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
	int				sign;

	if (l->d_small < 0)
		sign = -1;
	else
		sign = 1;
	if (l->i == ft_abs(l->d_big))
		return (l->d_small);
	coord = (((l->d_small * l->i) * 100) / ft_abs(l->d_big));
	if (ft_abs(coord % 100) > 50)
		coord = ((coord / 100) + (1 * sign));
	else
		coord /= 100;
	return (coord);
}

void			put_line_to_img(t_img_data *img, t_pix_prm a, t_pix_prm b)
{
	t_line_prm		l;
	t_grad_prms		clr;
	int				(*method)(t_line_prm*, int, int, int);

	if (a.x == b.x && a.y == b.y)
		return ;
	if (img->woo_prm == 0)
		method = &put_pix_to_img;
	if (img->woo_prm == 1)
		method = &put_woo_to_img;
	get_delta(&a, &b, &l);
	clr.delta = ft_abs(l.d_big);
	clr.a = a.color;
	clr.b = b.color;
	l.i = 0;
	l.img = img;
	while (l.i <= ft_abs(l.d_big))
	{
		if (l.d_ind == 1)
			method(&l, (a.x + (l.i * l.sign)), (a.y + get_coord(&l)), \
				get_grad_color(img, &clr, l.i));
		else
			method(&l, (a.x + get_coord(&l)), (a.y + (l.i * l.sign)), \
				get_grad_color(img, &clr, l.i));
		l.i++;
	}
}
