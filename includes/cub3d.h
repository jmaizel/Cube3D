#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "libft.h"
# include "get_next_line.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;

	t_texture	north_tex;
	t_texture	south_tex;
	t_texture	east_tex;
	t_texture	west_tex;

	int			ceiling_color;
	int			floor_color;

	// Image buffer
	void		*img;
	int			*img_data;
	int			bpp;
	int			size_line;
	int			endian;
}	t_game;

#endif
