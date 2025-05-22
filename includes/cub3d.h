/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:00:36 by jmaizel           #+#    #+#             */
/*   Updated: 2025/05/22 14:00:40 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/time.h>
# include <unistd.h>

/*
** Window dimensions
*/
# define WIN_WIDTH 1024
# define WIN_HEIGHT 720

/*
** Texture dimensions
*/
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

/*
** Game constants
*/
# define MAX_MONSTERS 20
# define M_PI 3.14159265358979323846
# define ROT_SPEED 0.05
# define MOVE_SPEED 0.1

/*
** Minimap colors
*/
# define MAP_BG_COLOR 0x222222
# define MAP_WALL_COLOR 0xE0E0E0
# define MAP_FLOOR_COLOR 0x303030
# define MAP_PLAYER_COLOR 0xFF2020
# define MAP_BORDER_COLOR 0x404040

/*
** Basic structures
*/
typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
}					t_map;

typedef struct s_texture
{
	void			*img;
	int				*data;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
}					t_texture;

typedef struct s_monster
{
	double			x;
	double			y;
	int				alive;
	int				frame;
	double			anim_time;
	double			anim_speed;
	int				health;
	int				max_health;
	int				hit_animation;
	double			hit_timer;
}					t_monster;

/*
** Ray-casting structures
*/
typedef struct s_ray
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	double			perp_wall_dist;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				hit_type;
}					t_ray;

/*
** Drawing structures
*/
typedef struct s_sprite
{
	double			x;
	double			y;
	int				width;
	int				height;
	int				screen_x;
	double			transform_y;
}					t_sprite;

typedef struct s_draw_params
{
	int				stripe;
	int				y;
	t_sprite		*sprite;
	int				tex_x;
	int				draw_start_y;
	int				draw_end_y;
}					t_draw_params;

typedef struct s_draw_limits
{
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start_y;
	int				draw_end_y;
}					t_draw_limits;

typedef struct s_minimap_size
{
	int				width;
	int				height;
}					t_minimap_size;

typedef struct s_minimap_pos
{
	int				x;
	int				y;
	int				cell_size;
}					t_minimap_pos;

typedef struct s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
}					t_line;

typedef struct s_point_dir
{
	int				x;
	int				y;
	int				dir_x;
	int				dir_y;
}					t_point_dir;

typedef struct s_weapon_pos
{
	int				x;
	int				y;
	int				width;
	int				height;
}					t_weapon_pos;

typedef struct s_weapon_draw
{
	int				start_x;
	int				start_y;
	int				x;
	int				y;
	int				draw_x;
	int				draw_y;
	int				color;
}					t_weapon_draw;

typedef struct s_tex_params
{
	int				tex_x;
	double			tex_pos;
	double			step;
}					t_tex_params;

/*
** Configuration structures
*/
typedef struct s_config_flags
{
	int				no_set;
	int				so_set;
	int				we_set;
	int				ea_set;
	int				f_set;
	int				c_set;
}					t_config_flags;

typedef struct s_map_check
{
	int				x;
	int				y;
	int				*count;
}					t_map_check;

/*
** Main game structure
*/
typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_player		player;

	t_texture		north_tex;
	t_texture		south_tex;
	t_texture		east_tex;
	t_texture		west_tex;

	t_texture		monster_frames[4];
	int				monster_frame_count;
	char			*monster_paths[4];

	int				ceiling_color;
	int				floor_color;
	int				keys[256];
	int				rotate_left;
	int				rotate_right;
	double			move_speed;
	double			rot_speed;

	double			last_frame_time;
	double			delta_time;

	int				door_opened;
	int				all_monsters_killed;
	int				victory_displayed;
	double			victory_timer;
	int				victory_final;
	t_texture		door_tex;

	t_texture		weapon_tex;
	char			*weapon_paths[4];

	t_monster		monsters[MAX_MONSTERS];
	int				monster_count;
	double			z_buffer[WIN_WIDTH];

	void			*img;
	int				*img_data;
	int				bpp;
	int				size_line;
	int				endian;

	int				firing;
	double			weapon_cooldown;
	double			weapon_timer;
	int				weapon_damage;
	double			weapon_range;
	t_texture		weapon_frames[4];
	int				weapon_frame_count;
	int				current_weapon_frame;
	int				weapon_animating;
	double			weapon_anim_time;
	double			weapon_anim_speed;

	t_texture		victory_tex;
}					t_game;

typedef struct s_config_data
{
	t_game			*game;
	int				*config_count;
	t_config_flags	*flags;
	int				phase;
}					t_config_data;

/*
** Movement functions
*/
int					is_valid_position(t_game *game, double x, double y);
void				move_forward(t_game *game);
void				move_backward(t_game *game);
void				move_left(t_game *game);
void				move_right(t_game *game);
void				rotate_left(t_game *game);
void				rotate_right(t_game *game);
void				handle_movement(t_game *game);

/*
** Input handling
*/
int					key_press(int keycode, t_game *game);
int					key_release(int keycode, t_game *game);

/*
** Game loop and timing
*/
int					game_loop(t_game *game);
double				get_time(void);
void				calculate_delta_time(t_game *game);
void				update_weapon_timer(t_game *game);

/*
** Monster functions
*/
void				init_monsters(t_game *game);
void				update_monster_hit_effects(t_game *game);
void				update_monster_animations(t_game *game);
int					all_monsters_dead(t_game *game);
void				process_monster_sprite(t_game *game, t_sprite *sprite,
						int monster_idx);
void				render_monsters(t_game *game);

/*
** Combat functions
*/
void				attack(t_game *game);
void				normalize_angle(double *angle);
void				init_weapon_animation(t_game *game);
int					is_monster_in_fov(t_game *game, double dx, double dy);
void				damage_monster(t_game *game, int monster_index);

/*
** Game status management
*/
void				check_monsters_status(t_game *game);
int					check_door_victory(t_game *game);
int					find_door_position(t_game *game, int *door_x, int *door_y);
int					display_victory(t_game *game);
void				update_victory_timer(t_game *game);

/*
** Drawing functions
*/
void				draw_controls_menu(t_game *game);
void				draw_minimap(t_game *game);
void				draw_line(t_game *game, t_line line, int color);
void				draw_cell(t_game *game, t_minimap_pos pos, int color);
void				draw_player_dot(t_game *game, int x, int y, int color);
void				draw_minimap_border(t_game *game, t_minimap_pos pos,
						t_minimap_size size);
void				draw_minimap_background(t_game *game, t_minimap_pos pos,
						t_minimap_size size);
void				draw_weapon(t_game *game);
void				render_frame(t_game *game);
void				draw_victory_message(t_game *game);

/*
** Texture handling
*/
void				get_texture(t_ray *ray, t_game *game, t_texture **tex);
void				calculate_texture_x(t_ray *ray, double *wall_x, int *tex_x,
						t_texture *tex);
int					load_texture(t_game *game, t_texture *texture, char *path);
int					load_all_textures(t_game *game);
void				draw_textured_line(int x, t_ray *ray, t_game *game);
int					apply_side_shading(int color);
int					change_door_color(int color);
void				free_texture_paths(t_game *game);
void				prepare_texture_params(t_ray *ray, t_texture *tex,
						t_tex_params *params);

/*
** Enemy drawing functions
*/
void				sort_monsters(t_game *game, double *distances, int *order);
int					get_monster_pixel(t_game *game, t_draw_params params,
						int monster_idx);
void				draw_monster_pixel(t_game *game, t_draw_params params,
						int color, int monster_idx);
void				draw_monster_column(t_game *game, t_draw_params draw,
						int monster_idx);
t_sprite			calc_sprite_pos(t_game *game, int *order, int i,
						t_sprite *sprite);
void				calc_sprite_draw_limits(t_sprite *sprite,
						t_draw_limits *limits);

/*
** Utils
*/
void				free_map(char **map);
int					exit_error(char *msg);
int					close_window(t_game *game);
void				cleanup_config_resources(t_game *game);
void				cleanup_texture_resources(t_game *game);

/*
** Raycasting
*/
void				init_ray(t_ray *ray, t_game *game, int x);
void				calculate_step_and_side_dist(t_ray *ray);
int					is_ray_hit(t_ray *ray, t_game *game);
void				perform_dda(t_ray *ray, t_game *game);
void				calculate_line_height(t_ray *ray);
void				raycasting(t_game *game);
void				safe_perform_dda(t_ray *ray, t_game *game);
void				complete_raycasting(t_game *game);
void				safe_draw_textured_line(int x, t_ray *ray, t_game *game);

/*
** Parsing
*/
char				**read_files_lines(const char *filename);
void				free_split(char **split);
int					parse_color_line(char *line);
int					parse_cub_file(const char *filename, t_game *game);
int					count_file_lines(int fd);
char				**allocate_lines(int fd, int count);
int					check_texture_duplication(int is_set, char *texture_type);
int					parse_texture_line(char *line, void **texture_img,
						int *is_set);
int					parse_color_config(char *line, int *color_ptr, int *is_set);
int					parse_weapon_frame(t_game *game, char *line, int index);
int					parse_monster_frame(t_game *game, char *line, int index);
int					is_map_start(char *line);
int					check_config_count(int config_count, int min_required,
						char *error_msg);
int					handle_unknown_config(int is_map_start_flag);
int					process_north_south(char *line, t_game *game,
						int *config_count, t_config_flags *flags);
int					process_west_east(char *line, t_game *game,
						int *config_count, t_config_flags *flags);
int					process_weapon_textures(char *line, t_game *game);
int					process_monster_textures(char *line, t_game *game);
int					parse_config(char **lines, t_game *game,
						int *map_start_index);
int					find_max_width(char **map_lines);
int					parse_map(char **lines, t_game *game, int start_index);
int					is_map_line(char *line);
int					is_map_interrupted(char **lines, int i);
int					handle_map_line(char **lines, int i, int *in_map,
						int *map_lines);
int					count_map_lines(char **lines, int start_index,
						int *map_start);
int					process_line(char *line, t_game *game, int *config_count,
						t_config_flags *flags);
int					is_texture_line(char *line);
int					handle_config(t_config_data *data, char *line);
int					check_texture_uniqueness(t_game *game);
int					validate_map_texture_coherence(t_game *game);
char				*ft_skip_whitespace(char *line);

/*
** Map validation
*/
int					is_map_closed(char **map, int width, int height);
void				init_player(t_game *game, int x, int y, char dir);
int					validate_map(t_game *game);
int					check_horizontal_bounds(char **map, int y, int x);
int					check_vertical_bounds(char **map, int y, int x);
int					is_cell_enclosed(char **map, int y, int x, int height);
int					process_map_char(t_game *game, char c, t_map_check *check);
void				init_player_north(t_game *game, int x, int y);
void				init_player_south(t_game *game, int x, int y);
void				init_player_east(t_game *game, int x, int y);
void				init_player_west(t_game *game, int x, int y);

#endif