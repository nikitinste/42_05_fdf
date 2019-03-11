/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fnctns_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:30:06 by uhand             #+#    #+#             */
/*   Updated: 2019/03/11 14:45:56 by uhand            ###   ########.fr       */
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
