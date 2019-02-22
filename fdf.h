/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 19:42:45 by uhand             #+#    #+#             */
/*   Updated: 2019/02/22 17:16:45 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# define BUF a->buf_str[a->buf_i]
# define WIN_X 0
# define WIN_Y 0

typedef struct	s_make_arr
{
	char			**buf_str;
	int				row_count;
	int				col_count;
	int				col_cnt_prev;
	int				row_i;
	int				buf_i;
}				t_make_arr;

typedef struct	s_map_prm
{
	int				x;
	int				y;
}				t_map_prm;

/* window params: win */

typedef struct	s_win_prm
{
	int				x;
	int				y;
	char			*name;
}				t_win_prm;

/* img */

typedef struct	s_img_data
{
	char			*addr;
	int				bpp;
	int				lsz;
	int				ndn;
	int				b_clr;
	int				woo_prm;
	t_win_prm		*win;
}				t_img_data;

/* Current dot params: a b */

typedef struct	s_pix_prm
{
	int				x;
	int				y;
	int				color;
}				t_pix_prm;

/* x */

typedef struct	s_mlx_prms
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_pix_prm		*a;
	t_pix_prm		*b;
	t_win_prm		*win;
	t_img_data		*img;
}				t_mlx_prms;

/* Input grad params: clr */

typedef struct	s_grad_prms
{
	int				delta;
	int				a;
	int				b;
}				t_grad_prms;

/* Operational grad params: grad */

typedef struct	s_grad
{
	unsigned char	*a;
	unsigned char	*b;
	unsigned char	*c;
	int				d_alpha;
	int				d1;
	int				d2;
	int				d3;
	int				color;
}				t_grad;

/* Operational build line params: l */

typedef struct	s_line_prm
{
	int				dx;
	int				dy;
	int				d_big;
	int				d_small;
	int				i;
	int				d_ind;
	int				sign;
	t_img_data		*img;
}				t_line_prm;

typedef struct	s_woo_prm
{
	int				pos;
	int				neg;
	int				origin;
}				t_woo_prm;

typedef struct	s_get_alpha
{
	int				remndr;
	int				p_dist;
	int				n_dist;
}				t_get_alpha;

int		error_msg(char *message);
int		col_count(char ***row);
int 	free_arr(int ***map, int ***color, t_make_arr *a, int err);
int		get_zeromap(t_make_arr *a, int ***map);
int		window_control(int ***map, int ***color, t_map_prm m, char *name);
int		get_color(char *str);
int		put_pix_to_img(t_line_prm *l, int x, int y, int color);
void	put_line_to_img(t_img_data *img, t_pix_prm a, t_pix_prm b);
int		put_woo_to_img(t_line_prm *l, int x, int y, int color);
//
void	print_image(t_img_data img, t_win_prm win);//! Убрать это потом!!
void	print_maps(int ***map, int ***color, t_map_prm m);
void	print_color(int color);
#endif
