/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emre149 <emre149@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:30:28 by emre149           #+#    #+#             */
/*   Updated: 2025/02/10 15:33:39 by emre149          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long long	ft_atoll(const char *str)
{
	long long	nbr;
	int			sign;

	nbr = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	while (ft_isdigit(*str))
		nbr = nbr * 10 + (*str++ - '0');
	return (nbr * sign);
}