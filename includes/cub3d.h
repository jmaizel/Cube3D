#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
// Dans cub3d.h, ajoute ces définitions :

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_texture
{
	void		*img;
	int			*data;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_texture;

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
	int			keys[256];
	int			rotate_left;
	int			rotate_right;
	double		move_speed;
	double		rot_speed;

	// Image buffer
	void		*img;
	int			*img_data;
	int			bpp;
	int			size_line;
	int			endian;
}				t_game;

typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

int				parse_cub_file(const char *filename, t_game *game);
void			free_map(char **map);
int				exit_error(char *msg);
int				parse_map(char **lines, t_game *game, int start_index);
int				validate_map(t_game *game);
void			get_texture(t_ray *ray, t_game *game, t_texture **tex);
void			draw_textured_line(int x, t_ray *ray, t_game *game);
void			raycasting(t_game *game);
void			calculate_step_and_side_dist(t_ray *ray);
void			init_ray(t_ray *ray, t_game *game, int x);
void			calculate_line_height(t_ray *ray);

void			safe_perform_dda(t_ray *ray, t_game *game);
void			safe_draw_textured_line(int x, t_ray *ray, t_game *game);
int				key_press(int keycode, t_game *game);
int				is_valid_position(t_game *game, double x, double y);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
int				close_window(t_game *game);
void			render_frame(t_game *game);
int				load_all_textures(t_game *game);
void			draw_minimap(t_game *game);
void			draw_gun(t_game *game);
int				game_loop(t_game *game);
int				key_release(int keycode, t_game *game);
#endif
