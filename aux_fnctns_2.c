/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fnctns_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:30:06 by uhand             #+#    #+#             */
/*   Updated: 2019/03/18 16:36:33 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		close_window(void *prm)
{
	t_mlx_prms	*x;

	x = (t_mlx_prms*)prm;
	mlx_destroy_window(x->mlx_ptr, x->win_ptr);
	exit(0);
	return (0);
}

void	renew_window(t_mlx_prms *mlx)
{
	clear_image(mlx->img, mlx->win);
	mlx_put_image_to_window(mlx->mlx_ptr, WIN, mlx->img_ptr, 0, 0);
	draw_image(mlx, mlx->v, mlx->map, mlx->color);
	mlx_put_image_to_window(mlx->mlx_ptr, WIN, mlx->img_ptr, 0, 0);
	if (mlx->v->help_rpm)
	{
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 7, (mlx->win->y - 85), \
			mlx->v->line_clr, "H - hide/show help | Mouse(L) - rotation | \
				Scroll - zoom & move(push)");
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 5, (mlx->win->y - 65), \
			mlx->v->line_clr, "Views: T - top, F - front, L - left , I - \
				isometric | 0 - reset scale");
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 5, (mlx->win->y - 45), \
			mlx->v->line_clr, "1 - off/on antialiasing | Asix rotation: \
				left-right/up-down/A-Z Z/Y/X");
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 5, (mlx->win->y - 25), \
			mlx->v->line_clr, "< > - change background color");
	}
}

void	set_scale(t_mlx_prms *x, t_view_prms *v)
{
	int		min_side;
	int		max_dim;

	if (x->win->x > x->win->y)
		min_side = x->win->y;
	else
		min_side = x->win->x;
	if (SCALE > 9 && SCALE < 51)
		v->scale = SCALE;
	else
		v->scale = 10;
	if ((v->scale * (x->m->x - 1)) > x->win->y || (v->scale * (x->m->y - 1)) \
		> x->win->x || v->scale * v->z_delta > min_side)
	{
		max_dim = set_max_dim((x->m->x - 1), (x->m->y - 1), v->z_delta);
		v->scale = min_side / max_dim;
	}
	if (v->scale < 2)
		v->scale = 2;
}

int		get_new_map(int row_count, int col_count, int ***map)
{
	int		row;

	if (!(map[0] = (int**)malloc(sizeof(int*) * row_count)))
		return (0);
	row = 0;
	while (row < row_count)
	{
		if (!(map[0][row] = (int*)malloc(sizeof(int) * col_count)))
		{
			while (--row >= 0)
				free(map[0][row]);
			free(map[0]);
			map[0] = NULL;
			return (0);
		}
		row++;
	}
	return (1);
}

int		get_invers_clr(int color, int ndn)
{
	int				start;
	int				inverse;
	int				i;
	unsigned char	*clr;
	unsigned char	*inv;

	if (ndn == 0)
		start = 0;
	else
		start = 1;
	inverse = 0;
	clr = (unsigned char *)&color;
	inv = (unsigned char *)&inverse;
	i = 0;
	while (i < 3)
	{
		inv[start + i] = 255 - clr[start + i];
		i++;
	}
	return (inverse);
}
