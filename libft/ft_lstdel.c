/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uhand <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 14:59:57 by uhand             #+#    #+#             */
/*   Updated: 2018/12/24 14:59:59 by uhand            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	**list;

	if (!alst || !*alst || !del)
		return ;
	list = alst;
	ft_lstdel(alst = &alst[0]->next, del);
	ft_lstdelone(list, del);
	list = alst;
}
