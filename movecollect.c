/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movecollect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:32:00 by tgoossen          #+#    #+#             */
/*   Updated: 2024/05/20 13:59:29 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	placeplayer(t_game *man)
{
	int	i;

	i = 0;
	man->map.x = 0;
	man->map.y = 0;
	while (man->map.y != man->map.y_end)
	{
		man->map.x = 0;
		while (man->map.fullmap[man->map.y][man->map.x] != '\0')
		{
			if (man->map.fullmap[man->map.y][man->map.x] == 'P')
			{
				mlx_image_to_window(man->mlx, man->images.player, man->map.x
					* 100, man->map.y * 100);
				i++;
			}
			if (man->map.fullmap[man->map.y][man->map.x] == 'E')
				i++;
			man->map.x++;
		}
		man->map.y++;
	}
	if (i > 2)
		man->map.countc = -1000000;
}

void	mapmake(t_game *man)
{
	while (man->map.y != man->map.y_end)
	{
		man->map.x = 0;
		while (man->map.fullmap[man->map.y][man->map.x] != '\0')
		{
			if (man->map.fullmap[man->map.y][man->map.x] == '0')
				draw_image(man, man->images.floor, man->map.x, man->map.y);
			else if (man->map.fullmap[man->map.y][man->map.x] == '1')
				draw_image(man, man->images.wall, man->map.x, man->map.y);
			else if (man->map.fullmap[man->map.y][man->map.x] == 'C')
			{
				draw_image(man, man->images.floor, man->map.x, man->map.y);
				man->images.coincount++;
				draw_image(man, man->images.coin, man->map.x, man->map.y);
			}
			else if (man->map.fullmap[man->map.y][man->map.x] == 'E')
				draw_image(man, man->images.end, man->map.x, man->map.y);
			else if (man->map.fullmap[man->map.y][man->map.x] == 'P')
				draw_image(man, man->images.floor, man->map.x, man->map.y);
			else
				man->map.countc = -11111111;
			man->map.x++;
		}
		man->map.y++;
	}
}

void	coindel(t_game *man)
{
	int	i;

	i = 0;
	while (man->images.coin->instances[i].x != man->map.next_x * 100
		|| man->images.coin->instances[i].y != man->map.next_y * 100)
		i++;
	man->images.coin->instances[i].z -= 1;
	man->map.fullmap[man->map.next_y][man->map.next_x] = '0';
	man->images.coincount--;
	ft_printf("coins to get = %d\n", man->images.coincount);
}

int	endgame(t_game *man, int dir, char axis)
{
	man->map.next_x = man->images.player->instances[0].x;
	man->map.next_y = man->images.player->instances[0].y;
	if (axis == 'x')
		man->map.next_x += dir;
	else if (axis == 'y')
		man->map.next_y += dir;
	man->map.next_x /= 100;
	man->map.next_y /= 100;
	if (man->map.fullmap[man->map.next_y][man->map.next_x] == '1')
		return (1);
	if (man->map.fullmap[man->map.next_y][man->map.next_x] == 'C')
		coindel(man);
	if (man->images.coincount == 0
		&& man->map.fullmap[man->map.next_y][man->map.next_x] == 'E')
	{
		ft_printf("you winnnn\n");
		man->images.player->instances[0].z -= 1;
		mlx_close_window(man->mlx);
	}
	return (0);
}

void	makewindow(t_game *man)
{
	man->mlx = mlx_init((man->map.x_end - 1) * 100, man->map.y_end * 100,
			"ballz", true);
	imageload(man);
	mapmake(man);
	placeplayer(man);
	if (checkwalls(man) == 1)
	{
		ft_printf("Error\nwalls_not_valid\n");
		exit(EXIT_FAILURE);
	}
	flood_fill(man, man->images.player->instances[0].x / 100,
		man->images.player->instances[0].y / 100);
	if (man->map.countc != man->images.coincount + 2 || man->map.countc == 2)
	{
		ft_printf("Error\nMAP_NOT_VALID\n");
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(man->mlx, &keydata, man);
	mlx_loop(man->mlx);
	mlx_terminate(man->mlx);
}
