/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_builder_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:18:05 by uhand             #+#    #+#             */
/*   Updated: 2019/02/19 20:20:16 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static int	get_alpha(t_line_prm *l, t_woo_prm *w, int color)
{
	t_get_alpha	a;

	w->reason = 0;
	if ((l->i + w->i) < 0 || (l->i + w->i) > l->d_big)
		return (0);
	a.coord = ((l->d_small * (l->i)) / ft_abs(l->d_big));
	a.w_coord = ((l->d_small * (l->i + w->i)) / ft_abs(l->d_big));
	if (a.w_coord > (a.coord - 2) && a.w_coord < (a.coord + 2))
		a.alp = (((l->d_small * (l->i + w->i)) * 100) / ft_abs(l->d_big)) % 100;
	else
		return (0);
	w->alpha = color;
	a.clr = (unsigned char*)&(w->alpha);
	if (l->img->ndn == 0)
		a.alp_i = 3;
	else
		a.alp_i = 0;
	if (a.clr[a.alp_i] == 0)
		a.clr[a.alp_i] = (255 * (100 - a.alp)) / 100;// - разобраться здесь!
	else
		a.clr[a.alp_i] = (a.clr[a.alp_i] * (100 - a.alp)) / 100;
	w->reason = 1;
	return (1);
}

void		put_woo_to_img(t_line_prm *l, int x, int y, int color)
{
	t_woo_prm	pos;
	t_woo_prm	neg;

	pos.i = 0;
	neg.i = 0;
	if (l->d_ind == 1)
		while (get_alpha(l, &pos, color) || get_alpha(l, &neg, color))
		{
			if (pos.reason)
				put_pix_to_img(l, (x + pos.i), y, pos.alpha);
			if (neg.reason)
				put_pix_to_img(l, (x + neg.i), y, neg.alpha);
			pos.i++;
			neg.i--;
		}
	if (l->d_ind == 0)
		while (get_alpha(l, &pos, color) || get_alpha(l, &neg, color))
		{
			if (pos.reason)
				put_pix_to_img(l, x, (y + pos.i), pos.alpha);
			if (neg.reason)
				put_pix_to_img(l, x, (y + neg.i), neg.alpha);
			pos.i++;
			neg.i--;
		}
}
