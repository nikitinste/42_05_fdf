/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <uhand@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:19:33 by uhand             #+#    #+#             */
/*   Updated: 2019/02/07 17:51:21 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

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

int		main(void)
{
	char	*str;
	int		color;

	str = "0xFFFFFF";
	color = get_color(str);
	printf("%d\n", color);
	printf("%X\n", color);
	return (0);
}
