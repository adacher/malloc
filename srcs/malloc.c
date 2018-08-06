/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:14:23 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:15:02 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_boxtype	*g_val = NULL;

static void	init_global_values(void)
{
	g_val->tiny = NULL;
	g_val->small = NULL;
	g_val->large = NULL;
}

void		*malloc(size_t size)
{
	if (size <= 0)
	{
		ft_putstr("Size must be greater than 0\n");
		return (NULL);
	}
	if (!g_val)
	{
		if ((g_val = mmap(NULL, sizeof(t_boxtype), PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_SHARED, -1, 0)) == NULL)
			return (NULL);
		init_global_values();
	}
	if ((check_which_size(size)) == 1)
		return (tors_malloc(size, &(g_val->tiny), 1));
	else if ((check_which_size(size)) == 2)
		return (tors_malloc(size, &(g_val->small), 2));
	else
		return (large_malloc(size, &(g_val->large)));
	return (NULL);
}
