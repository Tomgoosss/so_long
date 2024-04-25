/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomgoossens <tomgoossens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:30:57 by tgoossen          #+#    #+#             */
/*   Updated: 2024/03/21 19:24:41 by tomgoossens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_image(t_game *man, void *image, int x, int y)
{
	mlx_image_to_window(man->mlx, image, x * 100, y * 100);
}

void	imageload(t_game *man)
{
	mlx_texture_t	*c;
	mlx_texture_t	*e;
	mlx_texture_t	*f;
	mlx_texture_t	*p;
	mlx_texture_t	*w;

	c = mlx_load_png("pictures/coin.png");
	e = mlx_load_png("pictures/end.png");
	f = mlx_load_png("pictures/floor.png");
	p = mlx_load_png("pictures/marijn.png");
	w = mlx_load_png("pictures/wall.png");
	man->images.coin = mlx_texture_to_image(man->mlx, c);
	man->images.end = mlx_texture_to_image(man->mlx, e);
	man->images.floor = mlx_texture_to_image(man->mlx, f);
	man->images.player = mlx_texture_to_image(man->mlx, p);
	man->images.wall = mlx_texture_to_image(man->mlx, w);
	mlx_delete_texture(c);
	mlx_delete_texture(e);
	mlx_delete_texture(f);
	mlx_delete_texture(p);
	mlx_delete_texture(w);
}

void	set0(t_game *game)
{
	game->fd = 0;
	game->i = 0;
	game->num = 0;
	game->map.tempy = 0;
	game->map.tempx = 0;
	game->map.x_end = 0;
	game->map.y_end = 0;
	game->map.x = 0;
	game->map.y = 0;
	game->map.movemens = 0;
	game->images.coincount = 0;
	game->map.next_x = 0;
	game->map.next_x = 0;
	game->map.countc = 0;
}

int	main(int argc, char *argv[])
{
	t_game	*man;

	if (!argv[1] || argc > 2)
	{
		ft_printf("Error\n");
		exit(1);
	}
	man = (t_game *)malloc(sizeof(t_game));
	if (!man)
	{
		ft_printf("Error\nMALLOC_FAILED");
		exit(1);
	}
	set0(man);
	if (xycheck(man, argv) == 1)
	{
		ft_printf("Error\nMAP_NOT_VALID\n");
		exit(EXIT_FAILURE);
	}
	twodarray(man, argv);
	makewindow(man);
	return (EXIT_SUCCESS);
}
