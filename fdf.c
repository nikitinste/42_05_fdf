/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 19:42:57 by uhand             #+#    #+#             */
/*   Updated: 2019/03/20 15:11:14 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	make_color(t_make_arr *a, int ***color, int ***map)
{
	static int	call;
	char		*start;

	start = ft_strstr(BUF, ",0x");
	start += 3;
	if (!((*start >= '0' && *start <= '9') || (*start >= 'A' && *start <= 'F') \
		|| (*start >= 'a' && *start <= 'f')))
		return (0);
	if (call == 0)
	{
		if (!get_zeromap(a, color))
			return (free_arr(map, color, a, -1));
		call = 1;
	}
	color[0][a->row_i][a->buf_i] = get_color(start);
	return (1);
}

static int	get_row(t_list *list, t_make_arr *a, int ***map, int ***color)
{
	int		z;

	a->buf_str = ft_strsplit(list->content, ' ');
	a->col_count = col_count(&(a->buf_str));
	if (a->col_count != a->col_cnt_prev)
		return (free_arr(map, color, a, -1));
	a->col_cnt_prev = a->col_count;
	a->buf_i = 0;
	while (BUF)
	{
		if (ft_strstr(BUF, ",0x"))
			if (!make_color(a, color, map))
				return (0);
		z = ft_atoi(a->buf_str[a->buf_i]);
		map[0][a->row_i][a->buf_i] = z;
		a->buf_i++;
	}
	return (1);
}

static int	make_arr(t_list *list, int ***map, int ***color, t_map_prm *m)
{
	t_make_arr	a;

	a.row_count = ft_lstcount(list);
	a.buf_str = ft_strsplit(list->content, ' ');
	a.col_cnt_prev = col_count(&(a.buf_str));
	a.col_count = a.col_cnt_prev;
	free_arr(map, color, &a, 0);
	if (!get_zeromap(&a, map))
		return (free_arr(map, color, &a, -1));
	a.row_i = 0;
	while (a.row_i < a.row_count)
	{
		if (!get_row(list, &a, map, color))
			return (0);
		free_arr(map, color, &a, 0);
		a.row_i++;
		list = list->next;
	}
	m->x = a.row_count;
	m->y = a.col_count;
	return (1);
}

static int	read_map(char *file_name, t_list **l_ptr)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((ft_lstaddnext(l_ptr, line, (ft_strlen(line) + 1))) == -1)
		{
			ft_lstdel(l_ptr, &ft_lstfree);
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	if (ret == -1)
	{
		ft_lstdel(l_ptr, &ft_lstfree);
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int			main(int argc, char **argv)
{
	t_list		*list;
	t_map_prm	m;
	int			**map;
	int			**color;

	if (argc != 2)
		return (error_msg("usage: ./fdf map_file.fdf"));
	list = NULL;
	if (!read_map(argv[1], &list))
		return (error_msg("Map file error."));
	if (list == NULL)
		return (error_msg("Empty map_file"));
	color = NULL;
	if (!make_arr(list, &map, &color, &m))
	{
		ft_lstdel(&list, &ft_lstfree);
		return (error_msg("Invalid map."));
	}
	ft_lstdel(&list, &ft_lstfree);
	if (m.x == 1 && m.y == 1)
	{
		error_msg("Please set the correct map, at least two dots.");
		exit(0);
	}
	return (window_control(&map, &color, m, argv[1]));
}
