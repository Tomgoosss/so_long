/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:51:04 by tgoossen          #+#    #+#             */
/*   Updated: 2024/04/25 11:40:00 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>

typedef struct Map
{
	int			movemens;
	int			x_end;
	int			y_end;
	int			x;
	int			y;
	int			countc;
	int			tempx;
	int			tempy;
	int			next_x;
	int			next_y;
	char		*one_line;
	char		*all;
	char		**fullmap;
	char		**fullmapcheck;
}				t_map;

typedef struct Images
{
	mlx_image_t	*coin;
	mlx_image_t	*end;
	mlx_image_t	*floor;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	int			coincount;
}				t_images;

typedef struct Game
{
	int			fd;
	int			i;
	int			num;
	t_map		map;
	t_images	images;
	mlx_t		*mlx;
}				t_game;

void			makewindow(t_game *man);
void			keydata(mlx_key_data_t keydata, void *param);
int				xycheck(t_game *man, char *argv[]);
void			twodarray(t_game *man, char *argv[]);
int				endgame(t_game *man, int dir, char axis);
void			flood_fill(t_game *man, int pos_x, int pos_y);
void			imageload(t_game *man);
void			draw_image(t_game *man, void *image, int x, int y);
int				checkwalls(t_game *man);

#endif