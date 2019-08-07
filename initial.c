/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intial.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:38:08 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/29 11:12:10 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

int		ft_algo_ini(t_data *frac, int i)
{
	int			x;
	t_complex	c;
	int			y;
	int			res;

	y = -1;
	while (++y < 250)
	{
		x = -1;
		while (++x < 250)
		{
			c = (x / (double)62.5 - 2)
			+ ((y / (double)62.5 - 2) * I);
			if (i == 1)
				res = (ft_div(c, 100));
			if (i == 2)
				res = (ft_div2(c, 100, frac->julia));
			if (i == 3)
				res = (ft_div3(c, 100));
			frac->img_new_ptr[y * 250 + x] = ((1.5 * res * 0xCCEBFF) / 100);
		}
	}
	mlx_put_image_to_window(frac->mlx, frac->win, frac->img2, 750,
			250 * (i - 1));
	return (0);
}

int		main_init(t_data *frac)
{
	int	i;
	int	a;

	i = 5;
	frac->img2 = mlx_new_image(frac->mlx, 250, 250);
	frac->img_new_ptr = (int*)mlx_get_data_addr(frac->img2, &i, &i, &i);
	a = 0;
	while (++a < 4)
		ft_algo_ini(frac, a);
	return (0);
}
