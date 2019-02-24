/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fnctns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:12:00 by uhand             #+#    #+#             */
/*   Updated: 2019/02/24 13:57:31 by uhand            ###   ########.fr       */
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
			if (map[0][x][y] < 10)
				ft_putchar(' ');
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

void	print_image(t_img_data img, t_win_prm win)
{
	char	*img_str;
	int		line;
	int		i;

	img_str = (char*)img.addr;
	line = 0;
	while (line < (win.y * img.lsz))
	{
		i = 0;
		while (i < img.lsz)
		{
			img_str[line] = (char)120;
			ft_putnbr((int)img_str[line]);
			i++;
			line++;
		}
		ft_putchar('\n');
	}
}

void	print_win_param(t_win_prm *win, t_img_data *img)
{
	ft_putendl(win->name);
	ft_putnbr(win->x);
	ft_putchar('x');
	ft_putnbr(win->y);
	ft_putchar('\n');
	ft_putnbr(img->bpp);
	ft_putchar('\n');
	ft_putnbr(img->lsz);
	ft_putchar('\n');
	ft_putnbr(img->ndn);
	ft_putchar('\n');
}

void	print_color(int color)
{
	unsigned char	*clr_byte;

	clr_byte = (unsigned char*)&color;
	ft_putnbr(clr_byte[0]);
	ft_putchar(' ');
	ft_putnbr(clr_byte[1]);
	ft_putchar(' ');
	ft_putnbr(clr_byte[2]);
	ft_putchar(' ');
	ft_putnbr(clr_byte[3]);
	ft_putchar('\t');
}
