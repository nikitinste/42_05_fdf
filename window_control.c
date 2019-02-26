/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:34:00 by uhand             #+#    #+#             */
/*   Updated: 2019/02/26 18:09:43 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	clear_image(t_img_data *img, t_win_prm	*win)
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

static void	set_img_param(t_mlx_prms *x, t_img_data *img, t_view_prms *v, \
	t_perp_prms *p)
{
	img->b_clr = 0xFFFFFF;
	img->woo_prm = 1;
	img->far_prm = 0;
	x->v = v;
	v->proj = 0;
	v->x_ang = 0;
	v->y_ang = 0;
	v->z_ang = 0;
	if (SCALE > 9 && SCALE < 51)
		v->scale = SCALE;
	else
		v->scale = 10;
	v->x = x->win->x / 2;
	v->y = x->win->y / 2;
	v->p = p;
	v->line_clr = 0x000000;
	p->far = 100;
	p->height = 50;
}

static int	window_param(int ***map, t_map_prm m, t_win_prm *win, char *name)
{
	win->x = WIN_X;
	win->y = WIN_Y;
	win->name = ft_strjoin("fdf ", name);
	if ((win->x == 0 || win->y == 0) && map)
	{
		win->x = m.x * 20;
		win->y = m.y * 20;
	}
	return (1);
}

int			window_control(int ***map, int ***color, t_map_prm m, char *name)
{
	t_mlx_prms	x;
	t_win_prm	win;
	t_img_data	img;
	t_view_prms	v;
	t_perp_prms	p;

	print_maps(map, color, m);
	if (!window_param(map, m, &win, name))
		return (0/*free_maps(map, color, -1)*/);// написать эту ф-цию
	x.mlx_ptr = mlx_init();
	x.win_ptr = mlx_new_window(x.mlx_ptr, win.x, win.y, win.name);
	x.img_ptr = mlx_new_image (x.mlx_ptr, win.x, win.y);
	img.addr = mlx_get_data_addr (x.img_ptr, &img.bpp, &img.lsz, &img.ndn);	//
	print_win_param(&win, &img);//
	x.win = &win;
	x.img = &img;
	x.m = &m;
	img.win = &win;
	x.color = color;
	x.map = map;
	set_img_param(&x, &img, &v, &p);
	clear_image(x.img, x.win);
	mlx_put_image_to_window (x.mlx_ptr, x.win_ptr, x.img_ptr, 0, 0);
	draw_image(&x, &v, map, color);
	//put_line_to_img(&img, a, b);
	//print_image(img, win);
	mlx_put_image_to_window (x.mlx_ptr, x.win_ptr, x.img_ptr, 0, 0);
	mlx_hook(x.win_ptr, 2, 0, &deal_key, (void*)&x);
	mlx_hook(x.win_ptr, 17, 0, &close_window, (void*)&x);
	//mlx_key_hook(x.win_ptr, deal_key, (void*)&x);
	mlx_loop(x.mlx_ptr);
	return (0);
}
