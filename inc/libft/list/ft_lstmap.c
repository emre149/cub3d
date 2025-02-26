/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:56:06 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/10 16:14:52 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*element;

	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	while (lst->next)
	{
		element = ft_lstnew(f(lst->next->content));
		if (!element)
			return (ft_lstclear(&new, del), NULL);
		ft_lstadd_back(&new, element);
		lst = lst->next;
	}
	return (new);
}
