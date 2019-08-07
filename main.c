/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prastoin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 10:19:44 by prastoin          #+#    #+#             */
/*   Updated: 2019/01/29 15:53:44 by prastoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frac.h"

static void	*ft_algo(t_worker_arg *arg)
{
	const t_data	*frac = arg->frac;
	int				x;
	int				y;
	int				res;
	t_complex		c;

	y = arg->start_y - 1;
	while (++y < arg->end_y)
	{
		x = -1;
		while (++x < SCREEN_X)
		{
			c = (x / (double)frac->zoom + (frac->screenx))
				+ ((y / (double)frac->zoom + (frac->screeny)) * I);
			if (frac->pastfrac == 1)
				res = (ft_div(c, frac->iter));
			if (frac->pastfrac == 2)
				res = (ft_div2(c, frac->iter, frac->julia));
			if (frac->pastfrac == 3)
				res = (ft_div3(c, frac->iter));
			frac->img_ptr[y * SCREEN_X + x] =
				((1.5 * res * 0xCCEBFF) / frac->iter);
		}
	}
	return (NULL);
}

int			render(t_data *frac)
{
	pthread_t		threads[NBR_THREADS];
	t_worker_arg	args[NBR_THREADS];
	int				i;

	i = 0;
	frac->screeny = -(SCREEN_Y / (double)(frac->zoom * 2) + frac->position_y)
		+ frac->ymouse / 2;
	frac->screenx = -(SCREEN_X / (double)(frac->zoom * 2) + frac->position_x)
		+ frac->xmouse / 2;
	while (i < NBR_THREADS)
	{
		args[i] = (t_worker_arg) {
			.frac = frac,
				.start_y = i * (SCREEN_Y / (float)NBR_THREADS),
				.end_y = (i + 1) * (SCREEN_Y / (float)NBR_THREADS)
		};
		pthread_create(threads + i, NULL, (void*)ft_algo, args + i);
		i++;
	}
	while (i--)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(frac->mlx, frac->win, frac->img, 0, 0);
	return (0);
}

int			ft_load(t_data *frac, int argc)
{
	if (!(frac->win = mlx_new_window(frac->mlx, SCREEN_X + frac->all, SCREEN_Y,
			"Prastoin's frac.")))
		return (-1);
	if (!(frac->img = mlx_new_image(frac->mlx, SCREEN_X, SCREEN_Y)))
		return (-1);
	if (!(frac->img_ptr = (int *)mlx_get_data_addr(frac->img, &argc, &argc,
					&argc)))
		return (-1);
	mlx_key_hook(frac->win, deal_key, frac);
	mlx_mouse_hook(frac->win, mouse_hook, frac);
	mlx_hook(frac->win, 6, (1L << 6), funct, frac);
	return (0);
}

int			main(int argc, char **argv)
{
	t_data	frac;

	if (argc != 2)
		return (ft_error(0));
	if (ft_check_arg(argv[1], &frac) == -1)
		return (ft_error(0));
	frac.julia = 0.285 + 0.013 * I;
	ft_init(&frac);
	if (!(frac.mlx = mlx_init()))
		return (-1);
	if (ft_load(&frac, argc) == -1)
		return (ft_error(1));
	if (frac.frac == 4)
		main_init(&frac);
	render(&frac);
	mlx_loop(frac.mlx);
	return (0);
}
