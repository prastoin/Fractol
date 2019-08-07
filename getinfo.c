/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinfo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 11:35:32 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/29 15:54:12 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

int			ft_reload(t_data *frac)
{
	if (frac->all == 0)
	{
		mlx_destroy_image(frac->mlx, frac->img);
		mlx_destroy_window(frac->mlx, frac->win);
		frac->all = 250;
		frac->frac = 4;
		ft_load(frac, 1);
		main_init(frac);
	}
	else if (frac->all != 0)
	{
		mlx_destroy_image(frac->mlx, frac->img);
		mlx_destroy_window(frac->mlx, frac->win);
		frac->all = 0;
		frac->frac = frac->pastfrac;
		ft_load(frac, 1);
	}
	return (0);
}

int			deal_key(int key, t_data *frac)
{
	if (key == KEY_CTRL)
		ft_reload(frac);
	if (key == KEY_PLUS)
		frac->iter++;
	if (key == KEY_SPACE)
		frac->lock = frac->lock == 0 ? 1 : 0;
	if (key == KEY_UP)
		frac->position_y += (20 / frac->zoom);
	if (key == KEY_DOWN)
		frac->position_y -= (20 / frac->zoom);
	if (key == KEY_RIGHT)
		frac->position_x += (20 / frac->zoom);
	if (key == KEY_LEFT)
		frac->position_x -= (20 / frac->zoom);
	if (key == KEY_ESC)
	{
		mlx_destroy_image(frac->mlx, frac->img);
		mlx_destroy_window(frac->mlx, frac->win);
		exit(0);
	}
	mlx_destroy_image(frac->mlx, frac->img);
	frac->img = mlx_new_image(frac->mlx, SCREEN_X, SCREEN_Y);
	frac->img_ptr = (int *)mlx_get_data_addr(frac->img, &key, &key, &key);
	render(frac);
	return (0);
}

int			funct(int x, int y, t_data *frac)
{
	if (frac->lock == 0)
	{
		frac->julia = x / 200.0 - 2.5 + ((y / 200.0 - 2.5) * I);
		render(frac);
	}
	return (0);
}

static int	ft_cut_mouse_hook(int button, t_data *frac, int x, int y)
{
	if (button == 1 && x < 750)
	{
		frac->xmouse = x / (double)frac->zoom - (SCREEN_X
				/ (double)(frac->zoom * 2) + frac->position_x) + frac->xmouse;
		frac->ymouse = y / (double)frac->zoom - (SCREEN_Y
				/ (double)(frac->zoom * 2) + frac->position_y) + frac->ymouse;
		frac->position_y = 0;
		frac->position_x = 0;
		frac->zoom = frac->zoom * 2;
	}
	if (button == 4 && x < 750)
	{
		frac->xmouse = x / (double)frac->zoom - (SCREEN_X
				/ (double)(frac->zoom * 2) + frac->position_x) + frac->xmouse;
		frac->ymouse = y / (double)frac->zoom - (SCREEN_Y
				/ (double)(frac->zoom * 2) + frac->position_y) + frac->ymouse;
		frac->position_y = 0;
		frac->position_x = 0;
		frac->zoom = frac->zoom * 2;
	}
	if (button == 5)
		frac->zoom = frac->zoom * 0.5;
	render(frac);
	return (0);
}

int			mouse_hook(int button, int x, int y, t_data *frac)
{
	static int k;

	if (button == 2)
		frac->zoom = frac->zoom * 0.5;
	if (frac->frac == 4 || k)
	{
		if (button == 1 && x > 750)
		{
			main_init(frac);
			frac->frac = (y < 250 ? 1 : frac->frac);
			frac->frac = (y > 250 ? 2 : frac->frac);
			frac->frac = (y > 550 ? 3 : frac->frac);
			ft_init(frac);
		}
		if (frac->frac != 4)
			frac->pastfrac = frac->frac;
		k = 1;
	}
	ft_cut_mouse_hook(button, frac, x, y);
	return (0);
}
