/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:21:01 by uhand             #+#    #+#             */
/*   Updated: 2019/02/24 20:23:29 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

static void	get_coord_map()
{
	//
}

void	draw_image(t_mlx_prms *mlx, t_view_prms *v, int ***map, int ***color)
{
	static t_coords	crd;
	/*t_pix_prm	a;
	t_pix_prm	b;*/

	if (crd.x == NULL)
		if (!get_new_map(mlx->m->x, mlx->m->y, &crd.x) \
			|| !get_new_map(mlx->m->x, mlx->m->y, &crd.y))
			exit (0/*free_maps(map, color, -1)*/);// написать эту ф-цию
	if (mlx->img->far_prm == 1 && crd.far == NULL)
		if (!get_new_map(mlx->m->x, mlx->m->y, &crd.far))
			exit (0/*free_maps(map, color, -1)*/);// написать эту ф-цию
	get_coord_map();
	//
}
