/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:34:00 by uhand             #+#    #+#             */
/*   Updated: 2019/02/09 00:25:30 by stepa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	window_control(int ***map, int ***color, t_map_prm m)
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
