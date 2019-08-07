/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:37:41 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/23 11:15:34 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

int	ft_div3(t_complex c, int iter)
{
	t_complex	z;
	int			i;

	i = 0;
	z = 0;
	while (i < iter && cabs(z) <= 2)
	{
		z = ccos(z / c);
		i++;
	}
	return (i);
}

int	ft_div2(t_complex z, int iter, t_complex c)
{
	int			i;

	i = 0;
	while (i < iter && cabs(z) <= 2)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}

int	ft_div(t_complex c, int iter)
{
	t_complex	z;
	int			i;

	i = 0;
	z = 0;
	while (i < iter && cabs(z) <= 2)
	{
		z = z * z + c;
		i++;
	}
	return (i);
}
