/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomgoossens <tomgoossens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:30:32 by tgoossen          #+#    #+#             */
/*   Updated: 2024/03/21 19:24:50 by tomgoossens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	checkwalls(t_game *man)
{
	int	x;
	int	y;

	y = 0;
	while (y <= man->map.y_end)
	{
		x = 0;
		while (y == 0 && x <= man->map.x_end - 2)
		{
			if (man->map.fullmapcheck[y][x] != '1')
				return (1);
			x++;
		}
		y++;
		if (y < man->map.y_end)
		{
			if (man->map.fullmapcheck[y][0] != '1'
				|| man->map.fullmapcheck[y][man->map.x_end - 2] != '1')
				return (1);
		}
	}
	return (0);
}

void	flood_fill(t_game *man, int pos_x, int pos_y)
{
	if (pos_y < 0 || pos_y >= man->map.y_end || pos_x < 0
		|| pos_x >= man->map.x_end)
	{
		man->map.countc = -100000;
		return ;
	}
	if (man->map.fullmapcheck[pos_y][pos_x] == '1'
		|| man->map.fullmapcheck[pos_y][pos_x] == 'N')
		return ;
	else if (man->map.fullmapcheck[pos_y][pos_x] == 'C')
		man->map.countc++;
	else if (man->map.fullmapcheck[pos_y][pos_x] == 'E')
		man->map.countc++;
	else if (man->map.fullmapcheck[pos_y][pos_x] == 'P')
		man->map.countc++;
	else if (man->map.fullmapcheck[pos_y][pos_x] != '0')
		man->map.countc = -100000;
	man->map.fullmapcheck[pos_y][pos_x] = 'N';
	flood_fill(man, pos_x + 1, pos_y);
	flood_fill(man, pos_x - 1, pos_y);
	flood_fill(man, pos_x, pos_y + 1);
	flood_fill(man, pos_x, pos_y - 1);
}

void	keydata(mlx_key_data_t keydata, void *param)
{
	t_game	*man;

	man = (t_game *)param;
	man->map.tempx = man->images.player->instances[0].x;
	man->map.tempy = man->images.player->instances[0].y;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(man->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W && endgame(man, -100, 'y') == 0)
			man->images.player->instances[0].y -= 100;
		else if (keydata.key == MLX_KEY_S && endgame(man, +100, 'y') == 0)
			man->images.player->instances[0].y += 100;
		else if (keydata.key == MLX_KEY_A && endgame(man, -100, 'x') == 0)
			man->images.player->instances[0].x -= 100;
		else if (keydata.key == MLX_KEY_D && endgame(man, +100, 'x') == 0)
			man->images.player->instances[0].x += 100;
		if (man->map.tempx != man->images.player->instances[0].x
			|| man->map.tempy != man->images.player->instances[0].y)
			ft_printf("amount of moves = %d\n", man->map.movemens += 1);
	}
}

int	xycheck(t_game *man, char *argv[])
{
	int	temp;

	temp = 0;
	man->fd = open(argv[1], O_RDONLY);
	man->map.one_line = get_next_line(man->fd);
	if (!man->map.one_line)
	{
		close(man->fd);
		exit(1);
	}
	temp = strlen(man->map.one_line);
	while (man->map.one_line != NULL)
	{
		man->map.x_end = ft_strlen(man->map.one_line);
		if (man->map.x_end != temp)
			temp = 1;
		man->num += ft_strlen(man->map.one_line);
		ft_free(&man->map.one_line);
		man->map.one_line = get_next_line(man->fd);
		man->map.y_end++;
	}
	ft_free(&man->map.one_line);
	close(man->fd);
	return (temp);
}

void	twodarray(t_game *man, char *argv[])
{
	man->fd = open(argv[1], O_RDONLY);
	if (man->fd == -1)
	{
		ft_printf("Error\nfile could not read try other file\n");
		ft_free(&man->map.all);
		exit(EXIT_FAILURE);
	}
	man->map.all = malloc(man->num + 1);
	if (!man->map.all)
	{
		ft_printf("Error\nfile could not read try other file\n");
		ft_free(&man->map.all);
		exit(EXIT_FAILURE);
	}
	read(man->fd, man->map.all, man->num + 1);
	man->map.fullmap = ft_split(man->map.all, '\n');
	man->map.fullmapcheck = ft_split(man->map.all, '\n');
	ft_free(&man->map.all);
	close(man->fd);
}
