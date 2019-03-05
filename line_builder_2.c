/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_builder_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:18:05 by uhand             #+#    #+#             */
/*   Updated: 2019/03/05 15:37:08 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static int	get_woo_color(t_line_prm *l, int color, int alpha_i)
{
	unsigned char	*clr;
	int				alpha;

	clr = (unsigned char*)&color;
	if (l->img->ndn == 0)
		alpha = 3;
	else
		alpha = 0;
	if (clr[alpha] == 0)
		clr[alpha] = (255 * alpha_i) / 100;
	else
		clr[alpha] = 255 - (((255 - clr[alpha]) * (100 - alpha_i)) / 100);
	return (color);
}

static void	get_alpha(t_line_prm *l, t_woo_prm *woo)
{
	t_get_alpha	a;

	woo->pos = 0;
	woo->neg = 0;
	if (l->d_small == 0 && l->d_big == 0)
		a.remndr = 0;
	else
		a.remndr = (((ft_abs(l->d_small) * l->i) * 100) / ft_abs(l->d_big)) % 100;
	if (a.remndr == 0)
	{
		woo->origin = 0;
		return ;
	}
	if (a.remndr > 50)
	{
		woo->origin = 100 - a.remndr;
		woo->neg = 100 - woo->origin;
		return ;
	}
	if (a.remndr <= 50)
	{
		woo->origin = a.remndr;
		woo->pos = 100 - woo->origin;
		return ;
	}
}

int			put_woo_to_img(t_line_prm *l, int x, int y, int color)
{
	t_woo_prm	woo;
	int			sign;

	sign = 1;
	if (l->d_small < 0)
		sign = - 1;
	if (l->d_ind == 1)
	{
		get_alpha(l, &woo);
		if (woo.origin == 0)
			return (put_pix_to_img(l, x, y, color));
		if (woo.pos > woo.neg)
		{
			put_pix_to_img(l, x, y, get_woo_color(l, color, woo.origin));
			return (put_pix_to_img(l, x, (y + (1 * sign)), get_woo_color(l, \
				color, woo.pos)));
		}
		if (woo.pos < woo.neg)
		{
			put_pix_to_img(l, x, y, get_woo_color(l, color, woo.origin));
			return (put_pix_to_img(l, x, (y - (1 * sign)), get_woo_color(l, \
				color, woo.neg)));
		}
	}
	if (l->d_ind == 0)
	{
		get_alpha(l, &woo);
		if (woo.origin == 0)
			return (put_pix_to_img(l, x, y, color));
		if (woo.pos > woo.neg)
		{
			put_pix_to_img(l, x, y, get_woo_color(l, color, woo.origin));
			return (put_pix_to_img(l, (x + (1 * sign)), y, get_woo_color(l, \
				color, woo.pos)));
		}
		if (woo.pos < woo.neg)
		{
			put_pix_to_img(l, x, y, get_woo_color(l, color, woo.origin));
			return (put_pix_to_img(l, (x - (1 * sign)), y, get_woo_color(l, \
				color, woo.neg)));
		}
	}
	return (0);
}
