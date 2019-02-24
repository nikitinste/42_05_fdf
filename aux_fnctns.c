/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_fnctns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:55:10 by uhand             #+#    #+#             */
/*   Updated: 2019/02/24 19:23:38 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int		error_msg(char *message)
{
	ft_putendl(message);
	return (0);
}

int		col_count(char ***row)
{
	int		count;

	count = 0;
	while (row[0][count])
		count++;
	return (count);
}

int		get_zeromap(t_make_arr *a, int ***map)
{
	int		row;

	if (!(map[0] = (int**)malloc(sizeof(int*) * a->row_count)))
		return (0);
	row = 0;
	while (row < a->row_count)
	{
		if (!(map[0][row] = (int*)malloc(sizeof(int) * a->col_count)))
		{
			while (--row >= 0)
				free(map[0][row]);
			free(map[0]);
			map[0] = NULL;
			return (0);
		}
		ft_bzero(map[0][row], (sizeof(int) * a->col_count));
		row++;
	}
	return (1);
}

int		get_color(char *str)
{
	int		color;
	int		i;

	i = 2;
	color = 0;
	while (str[i] != '\0')
	{
		if (str[i] > 47 && str[i] < 58)
			color = ((color * 0x10) + str[i] - 48);
		if (str[i] > 64 && str[i] < 71)
			color = ((color * 0x10) + str[i] - 55);
		i++;
	}
	return (color);
}

int 	free_arr(int ***map, int ***color, t_make_arr *a, int err)
{
	int		i;

	i = 0;
	while (a->buf_str[i])
	{
		free(a->buf_str[i]);
		i++;
	}
	if (err == -1)
	{
		while (a->row_i >= 0)
		{
			if (map[0][a->row_i])
				free(map[0][a->row_i]);
			if (color[0] != NULL)
				if (color[0][a->row_i])
					free(color[0][a->row_i]);
			a->row_i--;
		}
		free (map[0]);
		if (color[0] != NULL)
			free (color[0]);
	}
	return (0);
}
