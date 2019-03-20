/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:21:01 by uhand             #+#    #+#             */
/*   Updated: 2019/03/20 20:56:31 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_coord_map(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd)
{
	t_coord_map	i;

	i.x = 0;
	v->far_min = 0;
	v->far_max = 0;
	while (i.x < mlx->m->x)
	{
		i.y = 0;
		while (i.y < mlx->m->y)
		{
			if (!get_magic(mlx, v, crd, &i))
				return (0);
			i.y++;
		}
		i.x++;
	}
	v->far_delta = v->far_max - v->far_min;
	return (1);
}

static void	set_hor_line(t_mlx_prms *mlx, t_coords *crd, t_draw_image *draw)
{
	draw->a.x = crd->x[draw->x][draw->y];
	draw->a.y = crd->y[draw->x][draw->y];
	draw->b.x = crd->x[draw->x][draw->y + 1];
	draw->b.y = crd->y[draw->x][draw->y + 1];
	if (mlx->v->clr_prm == 0 && mlx->color[0])
	{
		draw->a.color = mlx->color[0][draw->x][draw->y];
		if (draw->a.color == 0)
			draw->a.color = mlx->v->line_clr;
		if (draw->a.color == mlx->v->img->b_clr)
			draw->a.color = get_invers_clr(draw->a.color, mlx->v->img->ndn);
		draw->b.color = mlx->color[0][draw->x][draw->y + 1];
		if (draw->b.color == 0)
			draw->b.color = mlx->v->line_clr;
		if (draw->b.color == mlx->v->img->b_clr)
			draw->b.color = get_invers_clr(draw->b.color, mlx->v->img->ndn);
	}
	else if (mlx->v->clr_prm == 0)
	{
		draw->a.color = mlx->v->line_clr;
		draw->b.color = mlx->v->line_clr;
	}
	if (mlx->v->clr_prm == 1)
		set_high_color(mlx, draw, 0);
	check_far_param(mlx, crd, draw, 0);
}

static void	set_vert_line(t_mlx_prms *mlx, t_coords *crd, t_draw_image *draw)
{
	draw->a.x = crd->x[draw->x][draw->y];
	draw->a.y = crd->y[draw->x][draw->y];
	draw->b.x = crd->x[draw->x + 1][draw->y];
	draw->b.y = crd->y[draw->x + 1][draw->y];
	if (!(mlx->v->clr_prm) && mlx->color[0])
	{
		draw->a.color = mlx->color[0][draw->x][draw->y];
		if (draw->a.color == 0)
			draw->a.color = mlx->v->line_clr;
		if (draw->a.color == mlx->v->img->b_clr)
			draw->a.color = get_invers_clr(draw->a.color, mlx->v->img->ndn);
		draw->b.color = mlx->color[0][draw->x + 1][draw->y];
		if (draw->b.color == 0)
			draw->b.color = mlx->v->line_clr;
		if (draw->b.color == mlx->v->img->b_clr)
			draw->b.color = get_invers_clr(draw->b.color, mlx->v->img->ndn);
	}
	else if (mlx->v->clr_prm == 0)
	{
		draw->a.color = mlx->v->line_clr;
		draw->b.color = mlx->v->line_clr;
	}
	if (mlx->v->clr_prm == 1)
		set_high_color(mlx, draw, 1);
	check_far_param(mlx, crd, draw, 1);
}

static void	get_lines(t_mlx_prms *mlx, t_coords *crd, t_draw_image *draw)
{
	draw->x = 0;
	while (draw->x < (mlx->m->x - 1))
	{
		draw->y = 0;
		while (draw->y < (mlx->m->y - 1))
		{
			set_hor_line(mlx, crd, draw);
			put_line_to_img(mlx->img, draw->a, draw->b);
			set_vert_line(mlx, crd, draw);
			put_line_to_img(mlx->img, draw->a, draw->b);
			draw->y++;
		}
		set_vert_line(mlx, crd, draw);
		put_line_to_img(mlx->img, draw->a, draw->b);
		draw->x++;
	}
	draw->y = 0;
	while (draw->y < (mlx->m->y - 1))
	{
		set_hor_line(mlx, crd, draw);
		put_line_to_img(mlx->img, draw->a, draw->b);
		draw->y++;
	}
}

void		draw_image(t_mlx_prms *mlx, t_view_prms *v, int ***map,\
	int ***color)
{
	static t_coords	crd;
	static int		rec_counter;
	t_draw_image	draw;

	if (crd.x == NULL)
	{
		if (!get_new_map(mlx->m->x, mlx->m->y, &crd.x) \
			|| !get_new_map(mlx->m->x, mlx->m->y, &crd.y))
			close_fdf((void*)mlx);
		mlx->crd = &crd;
		crd.far = NULL;
	}
	if ((mlx->img->far_prm == 1 || v->proj == 1) && crd.far == NULL)
		if (!get_new_map(mlx->m->x, mlx->m->y, &crd.far))
			close_fdf((void*)mlx);
	crd.map = map;
	crd.color = color;
	if (!get_coord_map(mlx, v, &crd))
		persp_coord_recursive(mlx, &rec_counter);
	else
		rec_counter = 0;
	get_lines(mlx, &crd, &draw);
}
