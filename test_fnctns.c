/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fnctns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:12:00 by uhand             #+#    #+#             */
/*   Updated: 2019/02/11 16:15:46 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	print_maps(int ***map, int ***color, t_map_prm m)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < m.x)
	{
		while (y < m.y)
		{
			ft_putnbr(map[0][x][y]);
			ft_putchar(' ');
			/*if (map[0][x][y] < 10)
				ft_putchar(' ');*/
			y++;
		}
		ft_putchar('\n');
		y = 0;
		x++;
	}
	x = 0;
	ft_putchar('\n');
	if (color[0] != NULL)
	{
		while (x < m.x)
		{
			while (y < m.y)
			{
				ft_putnbr(color[0][x][y]);
				ft_putchar(' ');
				y++;
			}
			ft_putchar('\n');
			y = 0;
			x++;
		}
	}
}
