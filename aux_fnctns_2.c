/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fnctns_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:30:06 by uhand             #+#    #+#             */
/*   Updated: 2019/02/27 16:26:06 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

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
