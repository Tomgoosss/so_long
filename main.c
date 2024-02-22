#include "so_long.h"
void imageload(tgame *man);
void placeplayer(tgame *man);

void mapmake(tgame *man)
{

    while(man->map.y != man->map.y_end)
    {
		man->map.x = 0;
        while(man->map.fullmap[man->map.y][man->map.x] != '\0' )
        {
            if (man->map.fullmap[man->map.y][man->map.x] == '0')
                mlx_image_to_window(man->mlx, man->images.floor, man->map.x * 100, man->map.y * 100);
            else if (man->map.fullmap[man->map.y][man->map.x] == '1')
                mlx_image_to_window(man->mlx, man->images.wall, man->map.x * 100, man->map.y * 100);
            else if (man->map.fullmap[man->map.y][man->map.x] == 'C')
			{
				mlx_image_to_window(man->mlx, man->images.floor, man->map.x * 100, man->map.y * 100);
				man->images.coincount++;
                mlx_image_to_window(man->mlx, man->images.coin, man->map.x * 100, man->map.y * 100);
			}
            else if (man->map.fullmap[man->map.y][man->map.x] == 'E')
                mlx_image_to_window(man->mlx, man->images.end, man->map.x * 100, man->map.y * 100);
            else if (man->map.fullmap[man->map.y][man->map.x] == 'P')
				mlx_image_to_window(man->mlx, man->images.floor, man->map.x * 100, man->map.y * 100);
            man->map.x++;
        }
        man->map.y++;
    }
}

void placeplayer(tgame *man)
{
	man->map.x = 0;
	man->map.y = 0;

    while(man->map.y != man->map.y_end)
    {
		man->map.x = 0;
        while(man->map.fullmap[man->map.y][man->map.x] != '\0' )
        {
            if (man->map.fullmap[man->map.y][man->map.x] == 'P')
				mlx_image_to_window(man->mlx, man->images.player, man->map.x * 100, man->map.y * 100);
            man->map.x++;
        }
        man->map.y++;
	}
}

void makewindow(tgame *man)
{
	man->mlx = mlx_init((man->map.x_end - 1)* 100, man->map.y_end * 100, "ballz", true);
	imageload(man);
	mapmake(man);
	placeplayer(man);
	flood_fill(man, 4, 1);
	if(man->map.countCE != man->images.coincount + 2)
	{
		ft_printf("Error\nMAP_NOT_VALID\n");
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(man->mlx, &keydata, man);
	mlx_loop(man->mlx);
	mlx_terminate(man->mlx);
}

void imageload(tgame *man)
{
	mlx_texture_t *c;
	mlx_texture_t *e;
	mlx_texture_t *f;
	mlx_texture_t *p;
	mlx_texture_t *w;

	c = mlx_load_png("/home/tgoossen/Documents/so_long/pictures/coin.png");
	e = mlx_load_png("/home/tgoossen/Documents/so_long/pictures/end.png");
	f = mlx_load_png("/home/tgoossen/Documents/so_long/pictures/floor.png");
	p = mlx_load_png("/home/tgoossen/Documents/so_long/pictures/marijn.png");
	w = mlx_load_png("/home/tgoossen/Documents/so_long/pictures/wall.png");
	
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
void set0(tgame *game)
{
    game->fd = 0;
    game->i = 0;
    game->num = 0;
	game->map.tempy = 0;
	game->map.tempx = 0;
    game->map.x_end = 0;
    game->map.y_end = 0;
    game->map.playerx = 0;
    game->map.playery = 0;
    game->map.x = 0;
    game->map.y = 0;
	game->map.movemens = 0;
	game->images.coincount = 0;
	game->map.next_x = 0;
	game->map.next_x = 0;
	game->map.countCE = 0;
}

int main(int argc, char *argv[])
{
	tgame *man;
	int testvalid;

	if(!argv[1])
	{
		ft_printf("Error\nmap input invalid");
		exit(1);
	}
	argc = 0;
	testvalid = 0;
	man = (tgame *)malloc(sizeof(tgame));
	set0(man);
	testvalid = xycheck(man, argv);
	if (testvalid == 1)
	{
		ft_printf("Error\nMAP_NOT_VALID\n");
		exit(EXIT_FAILURE);
	}
	twodarray(man, argv);
	makewindow(man);
	exit(1);
	return(EXIT_SUCCESS);
}

