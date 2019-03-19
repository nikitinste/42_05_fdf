/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 19:42:45 by uhand             #+#    #+#             */
/*   Updated: 2019/03/19 16:29:22 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# define WIN_X 0
# define WIN_Y 0
# define DISP_X 2560
# define DISP_Y 1440
# define SCALE 20
# define BCLR 0x505050
# define HICLR 0xFF0000
# define LOWCLR 0x0000FF
# define BC x->img->b_clr
# define BUF a->buf_str[a->buf_i]
# define SCL v->scale
# define WIN mlx->win_ptr
# define OX mlx->v->x_ang
# define OY mlx->v->y_ang
# define OZ mlx->v->z_ang

typedef struct s_view_prms	t_view_prms;

/*
** Operational map array params: a
*/

typedef struct	s_make_arr
{
	char			**buf_str;
	int				row_count;
	int				col_count;
	int				col_cnt_prev;
	int				row_i;
	int				buf_i;
}				t_make_arr;

/*
** Map params: m
*/

typedef struct	s_map_prm
{
	int				x;
	int				y;
}				t_map_prm;

/*
** window params: win
*/

typedef struct	s_win_prm
{
	int				x;
	int				y;
	char			*name;
}				t_win_prm;

/*
** img
*/

typedef struct	s_img_data
{
	char			*addr;
	int				bpp;
	int				lsz;
	int				ndn;
	int				b_clr;
	int				woo_prm;
	int				far_prm;
	t_win_prm		*win;
}				t_img_data;

/*
** Mouse params: mouse
*/

typedef struct	s_mouse_crd
{
	int				i;
	int				x;
	int				y;
}				t_mouse_crd;

/*
** x || mlx
*/

typedef struct	s_mlx_prms
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_win_prm		*win;
	t_img_data		*img;
	t_map_prm		*m;
	t_view_prms		*v;
	t_mouse_crd		*scroll;
	t_mouse_crd		*mouse;
	int				***map;
	int				***color;
	int				x_i;
	int				y_i;
	int				z_i;
}				t_mlx_prms;

/*
** View params: v
*/

struct			s_view_prms
{
	int				proj;
	double			x_ang;
	double			y_ang;
	double			z_ang;
	int				scale;
	int				z_scl;
	int				scl_max;
	int				x;
	int				y;
	int				line_clr;
	int				scr_hold;
	int				mouse_hld;
	int				far;
	int				height;
	int				z_min;
	int				z_max;
	int				z_delta;
	int				far_min;
	int				far_max;
	int				far_delta;
	int				clr_prm;
	int				help_rpm;
	t_img_data		*img;
};

/*
** Coords: crd
*/

typedef struct	s_coords
{
	int				**x;
	int				**y;
	int				**far;
	int				***map;
	int				***color;
}				t_coords;

/*
** Window coords
*/

typedef struct	s_coord_map
{
	int				x;
	int				y;
	double			x_cr;
	double			y_cr;
	double			z_cr;
	double			x_crd;
	double			y_crd;
	double			z_crd;
}				t_coord_map;


/*
** Current dot params: a, b
*/

typedef struct	s_pix_prm
{
	int				x;
	int				y;
	int				color;
}				t_pix_prm;

/*
** Operational draw image params: draw
*/

typedef struct	s_draw_image
{
	t_pix_prm		a;
	t_pix_prm		b;
	int				x;
	int				y;
}				t_draw_image;

/*
** Input grad params: clr
*/

typedef struct	s_grad_prms
{
	int				delta;
	int				a;
	int				b;
}				t_grad_prms;

/*
** Operational grad params: grad
*/

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
	int				start;
	int				alpha;
}				t_grad;

/*
** Operational build line params: l
*/

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
	int				sign;
	int				x;
	int				y;
}				t_woo_prm;

typedef struct	s_get_alpha
{
	int				rem;
	int				p_dist;
	int				n_dist;
}				t_get_alpha;

int				error_msg(char *message);
int				col_count(char ***row);
int				free_arr(int ***map, int ***color, t_make_arr *a, int err);
int				get_zeromap(t_make_arr *a, int ***map);
int				get_new_map(int row_count, int col_count, int ***map);
int				window_control(int ***map, int ***color, t_map_prm m, \
	char *name);
int				get_color(char *str);
int				put_pix_to_img(t_line_prm *l, int x, int y, int color);
void			put_line_to_img(t_img_data *img, t_pix_prm a, t_pix_prm b);
int				put_woo_to_img(t_line_prm *l, int x, int y, int color);
void			clear_image(t_img_data *img, t_win_prm	*win);
int				deal_key(int key, void *prm);
int				mouse_press(int key, int x, int y, void *prm);
int				mouse_release(int key, int x, int y, void *prm);
int				mouse_move(int x, int y, void *prm);
int				close_window(void *param);
void			draw_image(t_mlx_prms *mlx, t_view_prms *v, int ***map, \
	int ***color);
int				get_invers_clr(int color, int ndn);
void			bump_up(double *angle, int *i, int a);
void			bump_down(double *angle, int *i, int a);
void			renew_window(t_mlx_prms *mlx);
int				mouse_scroll(t_mlx_prms *mlx, t_mouse_crd *scroll, int x, \
	int y);
int				mouse_button(t_mlx_prms *mlx, t_mouse_crd *mouse, int x, int y);
void			mouse_scale(int key, t_mlx_prms	*mlx);
void			bump_up(double *angle, int *i, int a);
void			bump_down(double *angle, int *i, int a);
void			left_iso(int key, t_mlx_prms	*x);
void			top_front(int key, t_mlx_prms	*x);
void			map_rotation(int key, t_mlx_prms	*x);
void			get_persp_cood(t_view_prms *v, t_coords *crd, t_coord_map *i);
void			get_magic(t_mlx_prms *mlx, t_view_prms *v, t_coords *crd, \
	t_coord_map *i);
void			set_grad_color(t_grad *g, t_grad_prms *clr, int pos);
void			set_scale(t_mlx_prms *x, t_view_prms *v);
void			set_z_limits(t_mlx_prms *x, t_view_prms *v);
void			set_high_color(t_mlx_prms *mlx, t_draw_image *draw, int prm);
int				get_grad_color(t_img_data *img, t_grad_prms *clr, int pos);
void			change_background(int key, t_mlx_prms *x);
int				set_max_dim(int a, int b, int c);
void			check_far_param(t_mlx_prms *mlx, t_coords *crd, \
	t_draw_image *draw, int prm);
void			set_alpha(t_mlx_prms *mlx, int *color, int alpha);
void			switch_params(int *param);
#endif
