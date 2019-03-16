/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:34:00 by uhand             #+#    #+#             */
/*   Updated: 2019/03/16 19:11:37 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		clear_image(t_img_data *img, t_win_prm *win)
{
	int		*image;
	int		i;
	int		lenth;

	image = (int*)img->addr;
	i = 0;
	lenth = win->x * win->y;
	while (i < (lenth))
	{
		image[i] = img->b_clr;
		i++;
	}
}

static void	set_first(t_mlx_prms *x, t_img_data *img, t_view_prms *v)
{
	img->b_clr = BCLR;
	img->woo_prm = 1;
	img->far_prm = 0;
	x->v = v;
	v->proj = 0;
	v->x_ang = 0;
	v->y_ang = 0;
	v->z_ang = 0;
	x->x_i = 0;
	x->y_i = 0;
	x->z_i = 0;
}

static void	set_img_param(t_mlx_prms *x, t_img_data *img, t_view_prms *v)
{
	unsigned int	i;

	set_first(x, img, v);
	set_scale(x, v);
	i = -1;
	if (x->m->x > x->m->y)
		v->scl_max = (i / 2) / (x->m->x - 1);
	else
		v->scl_max = (i / 2) / (x->m->y - 1);
	v->x = x->win->x / 2;
	v->y = x->win->y / 2;
	v->img = img;
	v->scr_hold = 0;
	v->mouse_hld = 0;
	if (x->color[0])
		v->line_clr = -1;
	else
		v->line_clr = get_invers_clr(img->b_clr, img->ndn);
	v->far = 100;
	v->height = 50;
}

static int	window_param(int ***map, t_map_prm m, t_win_prm *win, char *name)
{
	win->x = WIN_X;
	win->y = WIN_Y;
	win->name = ft_strjoin("fdf ", name);
	if ((win->x == 0 || win->y == 0) && map)
	{
		if (m.y < 2)
			win->x = SCALE * 4;
		else
			win->x = (m.y - 1) * SCALE * 4;
		if (win->x > DISP_X)
			win->x = DISP_X;
		if (win->x < 500)
			win->x = 500;
		if (m.x < 2)
			win->y = SCALE * 4;
		else
			win->y = (m.x - 1) * SCALE * 4;
		if (win->y > (DISP_Y - 45))
			win->y = DISP_Y - 45;
		if (win->y < 500)
			win->y = 500;
	}
	return (1);
}

int			window_control(int ***map, int ***color, t_map_prm m, char *name)
{
	t_mlx_prms	x;
	t_win_prm	win;
	t_img_data	img;
	t_view_prms	v;

	window_param(map, m, &win, name);
	x.mlx_ptr = mlx_init();
	x.win_ptr = mlx_new_window(x.mlx_ptr, win.x, win.y, win.name);
	x.img_ptr = mlx_new_image(x.mlx_ptr, win.x, win.y);
	img.addr = mlx_get_data_addr(x.img_ptr, &img.bpp, &img.lsz, &img.ndn);
	x.win = &win;
	x.img = &img;
	x.m = &m;
	img.win = &win;
	x.color = color;
	x.map = map;
	set_img_param(&x, &img, &v);
	renew_window(&x);
	mlx_hook(x.win_ptr, 2, 0, &deal_key, (void*)&x);
	mlx_hook(x.win_ptr, 17, 0, &close_window, (void*)&x);
	mlx_hook(x.win_ptr, 4, 0, &mouse_press, (void*)&x);
	mlx_hook(x.win_ptr, 5, 0, &mouse_release, (void*)&x);
	mlx_hook(x.win_ptr, 6, 0, &mouse_move, (void*)&x);
	mlx_loop(x.mlx_ptr);
	return (0);
}
