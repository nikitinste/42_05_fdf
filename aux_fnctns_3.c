/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fnctns_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:30:16 by uhand             #+#    #+#             */
/*   Updated: 2019/03/20 15:11:09 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		set_max_dim(int a, int b, int c)
{
	int		max;

	max = a;
	if (b > max)
		max = b;
	if (c > max)
		max = c;
	return (max);
}

void	set_alpha(t_mlx_prms *mlx, int *color, int alpha)
{
	unsigned char	*clr;
	int				i;

	clr = (unsigned char*)color;
	if (mlx->img->ndn == 0)
		i = 3;
	else
		i = 0;
	clr[i] = alpha;
}

void	switch_params(int *param)
{
	if (*param == 0)
		*param = 1;
	else
		*param = 0;
}

void	free_map(int **map, int i)
{
	i--;
	while (i >= 0)
	{
		if (map)
			free(map[i]);
		i--;
	}
}

int		free_all_maps(t_mlx_prms *mlx)
{
	free_map(mlx->map[0], mlx->m->x);
	free_map(mlx->color[0], mlx->m->x);
	free_map(mlx->crd->x, mlx->m->x);
	free_map(mlx->crd->y, mlx->m->x);
	free_map(mlx->crd->far, mlx->m->x);
	return (0);
}
