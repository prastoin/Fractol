/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 11:16:48 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/29 15:55:42 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

void			ft_init(t_data *frac)
{
	frac->xmouse = 0;
	frac->ymouse = 0;
	frac->zoom = (SCREEN_X + SCREEN_Y) / 8;
	frac->position_x = 0;
	frac->position_y = 0;
	frac->iter = 50;
	frac->lock = 1;
}

int				ft_error(int i)
{
	if (i == 0)
	{
		ft_putstr("./fractol [fractal] (mandel, julia, leaf, all)\n");
		return (0);
	}
	if (i == 1)
	{
		ft_putstr("Minilibx failed\n");
		return (0);
	}
	return (0);
}

static int		ft_cut_check_arg(char *str, t_data *frac)
{
	if (ft_strcmp(str, "leaf") == 0)
	{
		frac->pastfrac = 3;
		frac->frac = 3;
	}
	if (ft_strcmp(str, "all") == 0)
	{
		frac->pastfrac = 2;
		frac->frac = 4;
	}
	if (frac->frac == 0)
		return (-1);
	else
	{
		frac->all = frac->frac == 4 ? 250 : 0;
		return (0);
	}
}

int				ft_check_arg(char *str, t_data *frac)
{
	frac->frac = 0;
	frac->all = -1;
	if (ft_strcmp(str, "mandel") == 0)
	{
		frac->pastfrac = 1;
		frac->frac = 1;
	}
	if (ft_strcmp(str, "julia") == 0)
	{
		frac->pastfrac = 2;
		frac->frac = 2;
	}
	return (ft_cut_check_arg(str, frac));
}
