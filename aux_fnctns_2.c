/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fnctns_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 19:30:06 by uhand             #+#    #+#             */
/*   Updated: 2019/02/26 16:13:11 by uhand            ###   ########.fr       */
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