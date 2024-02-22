#include "so_long.h"

void flood_fill(tgame *man, int pos_x, int pos_y) 
{
	if (man->map.fullmapcheck[pos_y][pos_x] == '1' || man->map.fullmapcheck[pos_y][pos_x] == 'N')
        return;
	if (man->map.fullmapcheck[pos_y][pos_x] == 'C')
		man->map.countCE++;
	if (man->map.fullmapcheck[pos_y][pos_x] == 'E')
		man->map.countCE++;
	if (man->map.fullmapcheck[pos_y][pos_x] == 'P')
		man->map.countCE++;

	man->map.fullmapcheck[pos_y][pos_x] = 'N';
	flood_fill(man, pos_x + 1, pos_y);
	flood_fill(man, pos_x - 1, pos_y);
	flood_fill(man, pos_x, pos_y + 1);
	flood_fill(man, pos_x, pos_y - 1);
}


void coindel(tgame *man)
{
	int i;

	i = 0;
		while(man->images.coin->instances[i].x != man->map.next_x * 100 || man->images.coin->instances[i].y != man->map.next_y * 100)
			i++;
		man->images.coin->instances[i].z -= 1;
		man->map.fullmap[man->map.next_y][man->map.next_x] = '0';
		man->images.coincount--;
		ft_printf("coins to get = %d\n", man->images.coincount);
}

int endgame(tgame *man, int dir, char axis)
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
        return 1;
	 if (man->map.fullmap[man->map.next_y][man->map.next_x] == 'C')
		coindel(man);
	 if(man->images.coincount == 0 && man->map.fullmap[man->map.next_y][man->map.next_x] == 'E')
	 {
	 	ft_printf("you winnnn\n");
		man->images.player->instances[0].z -= 1;
		mlx_close_window(man->mlx);
	 }

    return 0;
}
void keydata(mlx_key_data_t keydata, void *param)
{
    tgame *man;

	man = (tgame *)param;
	man->map.tempx = man->images.player->instances[0].x;
	man->map.tempy = man->images.player->instances[0].y;
	 if(keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(man->mlx);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if(keydata.key == MLX_KEY_W && endgame(man, -100, 'y') == 0)
			man->images.player->instances[0].y -= 100;
		else if(keydata.key == MLX_KEY_S && endgame(man, +100, 'y') == 0)
			man->images.player->instances[0].y += 100;
		else if(keydata.key == MLX_KEY_A && endgame(man, -100, 'x') == 0)
			man->images.player->instances[0].x -= 100;
		else if(keydata.key == MLX_KEY_D && endgame(man, +100, 'x') == 0)
			man->images.player->instances[0].x += 100;
		if (man->map.tempx != man->images.player->instances[0].x || man->map.tempy != man->images.player->instances[0].y)
		{
			man->map.movemens += 1;
			ft_printf("amound of moves =%d\n", man->map.movemens);
		}
	}
}

int xycheck(tgame *man, char *argv[])
{
	int temp;
	temp = 0;
	man->fd = open(argv[1], O_RDONLY);
	man->map.one_line = get_next_line(man->fd);
	temp = strlen(man->map.one_line);
	while(man->map.one_line != NULL)
	{
		man->map.x_end = ft_strlen(man->map.one_line);
		if(man->map.x_end != temp)
			temp = 1;
		man->num += ft_strlen(man->map.one_line);
		ft_free(&man->map.one_line);
		man->map.one_line = get_next_line(man->fd);
		man->map.y_end++;
	}
	ft_free(&man->map.one_line);
	close(man->fd);
	return(temp);
}

void twodarray(tgame *man, char *argv[])
{
	man->fd = open(argv[1], O_RDONLY);
	if(man->fd == -1)
	{
		printf("Error\nfile could not read try other file\n");
		ft_free(&man->map.all);
		exit(EXIT_FAILURE);
	}
	man->map.all = malloc(man->num + 1);
	read(man->fd, man->map.all, man->num + 1);
	man->map.fullmap = ft_split(man->map.all, '\n');
	man->map.fullmapcheck = ft_split(man->map.all, '\n');
	ft_free(&man->map.all);
	close(man->fd);
}
