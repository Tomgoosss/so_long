#ifndef SO_LONG_h
#define SO_LONG_h


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

#define WIDTH 256
#define HEIGHT 256



typedef struct Map
{
	int movemens;
    int x_end;
    int y_end;
	int playerx;
	int playery;
    int x;
    int y;
	int countCE;
	int tempx;
	int tempy;
	int next_x;
	int next_y;
    char *one_line;
    char *all; 
    char **fullmap;
	char **fullmapcheck;
} tmap;

typedef struct Images
{
    mlx_image_t *coin;
    mlx_image_t *end;
    mlx_image_t *floor;
    mlx_image_t *player;
    mlx_image_t *wall;
	int coincount;
} timages;

typedef struct Game
{
    int fd;
    int i;
    int num;
    tmap map;
    timages images;
    mlx_t* mlx;
} tgame;

int xycheck(tgame *man, char *argv[]);
void twodarray(tgame *man, char *argv[]);
void setzero(tgame *man);
void keydata(mlx_key_data_t keydata, void *param);
void flood_fill(tgame *man, int pos_x, int pos_y);

#endif