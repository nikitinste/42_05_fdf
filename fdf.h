/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 19:42:45 by uhand             #+#    #+#             */
/*   Updated: 2019/02/07 21:26:12 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# define BUF a->buf_str[a->buf_i]

typedef struct	s_make_arr
{
	char	**buf_str;
	int		row_count;
	int		col_count;
	int		col_cnt_prev;
	int		row_i;
	int		buf_i;
}				t_make_arr;

typedef struct	s_map_prm
{
	int		x;
	int		y;
}				t_map_prm;

int		error_msg(char *message);
int		col_count(char ***row);
int 	free_arr(int ***map, int ***color, t_make_arr *a, int err);
int		get_zeromap(t_make_arr *a, int ***map);
void	window_control(int ***map, int ***color, t_map_prm m);
int		get_color(char *str);
#endif
