/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:21:01 by uhand             #+#    #+#             */
/*   Updated: 2019/03/08 15:08:04 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static void get_persp_cood(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd)
{
	if (mlx && v && crd)
		return ;
}

static void	get_coord_map(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd)
{
	int		x;
	int		y;
	double	x_cr;
	double	y_cr;
	double	z_cr;
	double	x_crd;
	double	y_crd;

	x = 0;
	if (v->proj == 0)
	{
		while (x < mlx->m->x)
		{
			y = 0;
			while (y < mlx->m->y)
			{
				x_cr = (x * SCL) - (((mlx->m->x - 1) * SCL) / 2);

				y_cr = (y * SCL) - (((mlx->m->y - 1) * SCL) / 2);

				z_cr = Z * SCL;

				z_cr = z_cr * cos(OX) + x_cr * sin(OX);
				x_cr = z_cr * (-sin(OX)) + x_cr * cos(OX);

				y_cr = y_cr * cos(OY) + x_cr * sin(OY);
				x_cr = y_cr * (-sin(OY)) + x_cr * cos(OY);

				y_cr = y_cr * cos(OZ) - z_cr * sin(OZ);
				z_cr = (-y_cr) * sin(OZ) + z_cr * cos(OZ);


				x_crd = x_cr;

				y_crd = -z_cr;

				crd->x[x][y] = (double)v->x + x_crd;

				crd->y[x][y] = (double)v->y + y_crd;

				if (mlx->img->far_prm == 1)
					crd->far[x][y] = 0;// temporary value
				y++;
			}
			x++;
		}
	}
	else
		get_persp_cood(mlx, v, crd);
}

static void	set_hor_line(t_coords *crd, t_draw_image *draw, \
	t_view_prms *v, int ***color)
{
	draw->a.x = crd->x[draw->x][draw->y];
	draw->a.y = crd->y[draw->x][draw->y];
	draw->b.x = crd->x[draw->x][draw->y + 1];
	draw->b.y = crd->y[draw->x][draw->y + 1];
	if (v->line_clr < 0 && color[0])
	{
		draw->a.color = color[0][draw->x][draw->y];
		if (draw->a.color == v->img->b_clr)
			draw->a.color = get_invers_clr(draw->a.color, v->img->ndn);
		draw->b.color = color[0][draw->x][draw->y + 1];
		if (draw->b.color == v->img->b_clr)
			draw->b.color = get_invers_clr(draw->b.color, v->img->ndn);
	}
	else
	{
		draw->a.color = v->line_clr;
		draw->b.color = v->line_clr;
	}
}

static void	set_vert_line(t_coords *crd, t_draw_image *draw, \
	t_view_prms *v, int ***color)
{
	draw->a.x = crd->x[draw->x][draw->y];
	draw->a.y = crd->y[draw->x][draw->y];
	draw->b.x = crd->x[draw->x + 1][draw->y];
	draw->b.y = crd->y[draw->x + 1][draw->y];
	if (v->line_clr < 0 && color[0])
	{
		draw->a.color = color[0][draw->x][draw->y];
		if (draw->a.color == v->img->b_clr)
			draw->a.color = get_invers_clr(draw->a.color, v->img->ndn);
		draw->b.color = color[0][draw->x + 1][draw->y];
		if (draw->b.color == v->img->b_clr)
			draw->b.color = get_invers_clr(draw->b.color, v->img->ndn);
	}
	else
	{
		draw->a.color = v->line_clr;
		draw->b.color = v->line_clr;
	}
}

void	draw_image(t_mlx_prms *mlx, t_view_prms *v, int ***map, int ***color)
{
	static t_coords	crd;
	t_draw_image	draw;

	if (crd.x == NULL)
		if (!get_new_map(mlx->m->x, mlx->m->y, &crd.x) \
			|| !get_new_map(mlx->m->x, mlx->m->y, &crd.y))
			exit (0/*free_maps(map, color, -1)*/);// написать эту ф-цию
	if (mlx->img->far_prm == 1 && crd.far == NULL)
		if (!get_new_map(mlx->m->x, mlx->m->y, &crd.far))
			exit (0/*free_maps(map, color, -1)*/);// написать эту ф-цию
	crd.map = map;
	crd.color = color;
	get_coord_map(mlx, v, &crd);
	draw.x = 0;
	while (draw.x < (mlx->m->x - 1))
	{
		draw.y = 0;
		while (draw.y < (mlx->m->y - 1))
		{
			set_hor_line(&crd, &draw, v, color);
			put_line_to_img(mlx->img, draw.a, draw.b);
			set_vert_line(&crd, &draw, v, color);
			put_line_to_img(mlx->img, draw.a, draw.b);
			draw.y++;
		}
		set_vert_line(&crd, &draw, v, color);
		put_line_to_img(mlx->img, draw.a, draw.b);
		draw.x++;
	}
	draw.y = 0;
	while (draw.y < (mlx->m->y - 1))
	{
		set_hor_line(&crd, &draw, v, color);
		put_line_to_img(mlx->img, draw.a, draw.b);
		draw.y++;
	}
}
