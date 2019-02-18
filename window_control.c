/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:34:00 by uhand             #+#    #+#             */
/*   Updated: 2019/02/18 16:22:37 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	clear_window(t_img_data *img, t_win_prm	*win)
{
	int		*image;
	int		i;
	int		lenth;

	image = (int*)img->addr;
	i = 0;
	lenth = win->x * win->y;
	while (i < (lenth))
	{
		image[i] = 0x000000;
		i++;
	}
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
static int	deal_key(int key, void *prm)
{
	t_mlx_prms	*x;

	x = (t_mlx_prms*)prm;
	if (key == 53)
	{
		ft_putnbr(key);
		mlx_destroy_window (x->mlx_ptr, x->win_ptr);
		exit (0);
	}
	if (key == 126)
		x->b->y -= 15;
	if (key == 125)
		x->b->y += 15;
	if (key == 124)
		x->b->x += 15;
	if (key == 123)
		x->b->x -= 15;
	if (key == 13)
		x->a->y -= 15;
	if (key == 1)
		x->a->y += 15;
	if (key == 2)
		x->a->x += 15;
	if (key == 0)
		x->a->x -= 15;
	clear_window(x->img, x->win);
	put_line_to_img(*x->img, *x->a, *x->b);
	mlx_put_image_to_window (x->mlx_ptr, x->win_ptr, x->img_ptr, 0, 0);
	return (0);
}

int			window_control(int ***map, int ***color, t_map_prm m, char *name)
{
	t_mlx_prms	x;
	t_win_prm	win;
	t_img_data	img;
	t_pix_prm	a;
	t_pix_prm	b;

	print_maps(map, color, m);
	if (!window_param(map, m, &win, name))
		return (0/*free_maps(map, color, -1)*/);// написать эту ф-цию
	x.mlx_ptr = mlx_init();
	x.win_ptr = mlx_new_window(x.mlx_ptr, win.x, win.y, win.name);
	x.img_ptr = mlx_new_image (x.mlx_ptr, win.x, win.y);
	img.addr = mlx_get_data_addr (x.img_ptr, &img.bpp, &img.lsz, &img.ndn);
	//
	ft_putendl(win.name);
	ft_putnbr(win.x);
	ft_putchar('x');
	ft_putnbr(win.y);
	ft_putchar('\n');
	ft_putnbr(img.bpp);
	ft_putchar('\n');
	ft_putnbr(img.lsz);
	ft_putchar('\n');
	ft_putnbr(img.ndn);
	ft_putchar('\n');
	//
	a.x = 0;
	a.y = 0;
	a.color = 0xFF0000;
	b.x = win.x;
	b.y = win.y;
	x.a = &a;
	x.b = &b;
	x.win = &win;
	x.img = &img;
	b.color = 0x00FF00;
	img.win = &win;
	put_line_to_img(img, a, b);
	//print_image(img, win);
	mlx_put_image_to_window (x.mlx_ptr, x.win_ptr, x.img_ptr, 0, 0);
	mlx_key_hook(x.win_ptr, deal_key, (void*)&x);
	mlx_loop(x.mlx_ptr);
	return (0);
}
