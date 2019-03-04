/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 18:10:38 by uhand             #+#    #+#             */
/*   Updated: 2019/03/04 19:24:19 by uhand            ###   ########.fr       */
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

int		mouse_move(int x, int y, void *prm)
{
	static t_mouse_crd	mouse;
	t_mlx_prms			*mlx;

	mlx = (t_mlx_prms*)prm;
	if (mlx->v->scr_hold == 1 && mouse.i == 0)
	{
		mouse.i = 1;
		mouse.x = x;
		mouse.y = y;
		mlx->mouse = &mouse;
		return (0);
	}
	if (mlx->v->scr_hold == 1 && mouse.i == 1)
	{
		mlx->v->x += (x - mouse.x);
		mlx->v->y += (y - mouse.y);
		mouse.x = x;
		mouse.y = y;
		clear_image(mlx->img, mlx->win);
		mlx_put_image_to_window (mlx->mlx_ptr, WIN, mlx->img_ptr, 0, 0);
		draw_image(mlx, mlx->v, mlx->map, mlx->color);
		mlx_put_image_to_window (mlx->mlx_ptr, WIN, mlx->img_ptr, 0, 0);
	}
	return (0);
}

int		mouse_release(int key, int x, int y, void *prm)
{
	t_mlx_prms	*mlx;

	mlx = (t_mlx_prms*)prm;
	if (x && y)
	{
		if (key == 3)
		{
			mlx->v->scr_hold = 0;
			mlx->mouse->i = 0;
		}
	}
	return (0);
}

int		mouse_press(int key, int x, int y, void *prm)
{
	t_mlx_prms	*mlx;

	mlx = (t_mlx_prms*)prm;
	if (x >= 0 && x < mlx->win->x && y >= 0 && y < mlx->win->y)
	{
		if (key == 5)
		{
			if (mlx->v->scale >= 50)
			{
				if (mlx->v->scale < (mlx->v->scl_max + 5))
					mlx->v->scale += 5;
			}
			else if (mlx->v->scale < mlx->v->scl_max)
					mlx->v->scale++;
		}
		if (key == 4)
		{
			if (mlx->v->scale > 50)
					mlx->v->scale -= 5;
			else if (mlx->v->scale > 2)
					mlx->v->scale--;
		}
		if (key == 3)
		{
			mlx->v->scr_hold = 1;
			return (0);
		}
		//ft_putnbr(mlx->v->scale);
		//ft_putchar('\n');
		clear_image(mlx->img, mlx->win);
		mlx_put_image_to_window (mlx->mlx_ptr, WIN, mlx->img_ptr, 0, 0);
		draw_image(mlx, mlx->v, mlx->map, mlx->color);
		mlx_put_image_to_window (mlx->mlx_ptr, WIN, mlx->img_ptr, 0, 0);
	}
	return (0);
}

/*int		key_release(int key, void *prm)
{
	//
}*/

int		deal_key(int key, void *prm)
{
	t_mlx_prms	*x;
	static int	z_i;

	x = (t_mlx_prms*)prm;
	if (key == 53)
	{
		ft_putnbr(key);
		mlx_destroy_window (x->mlx_ptr, x->win_ptr);
		exit (0);
	}
	if (key == 123)
	{
		if (z_i <= 71)
			z_i += 1;
		if (z_i >= 72)
			z_i = 0;
		x->v->z_ang = (M_PI * z_i) / 36;
		/*if (x->v->y_ang < 2)
			x->v->y_ang += 0.05;
		if (x->v->y_ang >= 2)
			x->v->y_ang = 0;*/
	}
	if (key == 124)
	{
		if (z_i >= 0)
			z_i -= 1;
		if (z_i == -1)
			z_i = 71;
		x->v->z_ang = (M_PI * z_i) / 36;
		/*if (x->v->y_ang > 0)
			x->v->y_ang -= 0.05;
		if (x->v->y_ang == 0)
			x->v->y_ang = 1.95;*/
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
		x->a->x -= 2;*/
	if (key == 18)
	{
		if (x->img->woo_prm == 0)
			x->img->woo_prm = 1;
		else
			x->img->woo_prm = 0;
	}
	clear_image(x->img, x->win);
	mlx_put_image_to_window (x->mlx_ptr, x->win_ptr, x->img_ptr, 0, 0);
	draw_image(x, x->v, x->map, x->color);
	mlx_put_image_to_window (x->mlx_ptr, x->win_ptr, x->img_ptr, 0, 0);
	return (0);
}
