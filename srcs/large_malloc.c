/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:13:43 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:14:14 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*large_mmap(size_t size)
{
	t_box	*box;

	if ((box = mmap(NULL, size + BOX, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_SHARED, -1, 0)) == (void *)-1)
		return (NULL);
	return (box);
}

void		*large_malloc(size_t size, t_box **addr)
{
	t_box	*tmp;
	void	*ptr;

	if (!(*addr))
	{
		if ((ptr = large_mmap(size)) == NULL)
			return (NULL);
		(*addr) = init_box_large(size, ptr, 3);
		return ((*addr)->data);
	}
	else
	{
		tmp = *addr;
		while (tmp->next)
			tmp = tmp->next;
		if ((ptr = large_mmap(size)) == NULL)
			return (NULL);
		tmp->next = init_box_large(size, ptr, 3);
		tmp->next->prev = tmp;
		return (tmp->next->data);
	}
}
