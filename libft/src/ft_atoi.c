/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:08:11 by seunan            #+#    #+#             */
/*   Updated: 2023/07/18 15:38:26 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long long	num;
	int			neg;

	num = 0;
	neg = 1;
	while (*str == ' ')
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		++str;
	}
	while (('0' <= *str && *str <= '9'))
	{
		num = num * 10 + *str - '0';
		++str;
	}
	return (neg * num);
}