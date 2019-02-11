/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:40:13 by uhand             #+#    #+#             */
/*   Updated: 2018/12/24 18:40:15 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(void *content, size_t size)
{
	if (content && size)
	{
		ft_bzero(content, size);
		free(content);
		content = NULL;
	}
}
