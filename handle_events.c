/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:10:38 by uhand             #+#    #+#             */
/*   Updated: 2019/02/26 18:01:34 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int close_window(void *prm)
{
	t_mlx_prms	*x;

	x = (t_mlx_prms*)prm;
	mlx_destroy_window (x->mlx_ptr, x->win_ptr);
    exit(0);
    return (0);
}

int		deal_key(int key, void *prm)
{
	t_mlx_prms	*x;

	x = (t_mlx_prms*)prm;
	if (key == 53)
	{
		ft_putnbr(key);
		mlx_destroy_window (x->mlx_ptr, x->win_ptr);
		exit (0);
	}
	/*if (key == 126)
		x->b->y -= 2;
	if (key == 125)
		x->b->y += 2;
	if (key == 124)
		x->b->x += 2;
	if (key == 123)
		x->b->x -= 2;
	if (key == 13)
		x->a->y -= 2;
	if (key == 1)
		x->a->y += 2;
	if (key == 2)
		x->a->x += 2;
	if (key == 0)
		x->a->x -= 2;
	if (key == 18)*/
	{
		if (x->img->woo_prm == 0)
			x->img->woo_prm = 1;
		else
			x->img->woo_prm = 0;
	}
	clear_image(x->img, x->win);
	mlx_put_image_to_window (x->mlx_ptr, x->win_ptr, x->img_ptr, 0, 0);
	draw_image(x, x->v, x->map, x->color);
	//put_line_to_img(x->img, *x->a, *x->b);
	mlx_put_image_to_window (x->mlx_ptr, x->win_ptr, x->img_ptr, 0, 0);
	return (0);
}
