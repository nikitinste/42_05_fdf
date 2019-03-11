/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:18:06 by uhand             #+#    #+#             */
/*   Updated: 2019/03/11 13:48:24 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static int	get_grad_color(t_img_data *img, t_grad_prms *clr, int pos)
{
	t_grad			grad;

	if (clr->a == clr->b || pos == 0)
		return (clr->a);
	if (img->ndn == 0)
	{
		grad.start = 0;
		grad.alpha = 3;
	}
	else
	{
		grad.start = 1;
		grad.alpha = 0;
	}
	set_gard_color(&grad, clr, pos);
	return (grad.color);
}

static void	get_delta(t_pix_prm *a, t_pix_prm *b, t_line_prm *l)
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

static int	get_coord(t_line_prm *l)
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

static void	build_line(t_line_prm *l, t_pix_prm *a, t_grad_prms *clr, \
	int (*method)(t_line_prm*, int, int, int))
{
	while (l->i <= ft_abs(l->d_big))
	{
		if (l->d_ind == 1)
			method(l, (a->x + (l->i * l->sign)), (a->y + get_coord(l)), \
				get_grad_color(l->img, clr, l->i));
		else
			method(l, (a->x + get_coord(l)), (a->y + (l->i * l->sign)), \
				get_grad_color(l->img, clr, l->i));
		l->i++;
	}
}

void		put_line_to_img(t_img_data *img, t_pix_prm a, t_pix_prm b)
{
	t_line_prm		l;
	t_grad_prms		clr;
	int				(*method)(t_line_prm*, int, int, int);

	if (a.x == b.x && a.y == b.y)
		return ;
	if (((a.x < 0 || a.x >= img->win->x) || (a.y < 0 || a.y >= img->win->y)) \
		&& ((b.x < 0 || b.x >= img->win->x) || (b.y < 0 || b.y >= img->win->y)))
			return ;
	if (img->woo_prm == 0)
		method = &put_pix_to_img;
	if (img->woo_prm == 1)
		method = &put_woo_to_img;
	get_delta(&a, &b, &l);
	if (l.d_big == 0)
		return ;
	clr.delta = ft_abs(l.d_big);
	clr.a = a.color;
	clr.b = b.color;
	l.i = 0;
	l.img = img;
	build_line(&l, &a, &clr, method);
}
