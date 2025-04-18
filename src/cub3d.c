/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhami <nbenhami@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:43:10 by nbenhami          #+#    #+#             */
/*   Updated: 2025/04/17 15:32:54 by nbenhami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	void	*mlx;
	void	*win;
	t_game	*game;

	if (ac != 2)
		return (printf("Error : ./cub3d [map name].cub\n"), 1);
	if (check_file(av[1]) == FALSE)
		return (1);
	mlx = mlx_init();
	if (!mlx)
		return (1);
	win = mlx_new_window(mlx, 1080, 720, "KAWABUNGA");
	if (!win)
		return (1);
	game = new_game(mlx, win, DEBUG);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 2, 1L << 0, key_hook, game);
	mlx_loop(mlx);
	return (0);
}
