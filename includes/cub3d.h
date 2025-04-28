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
# define MAX_MONSTERS 20
# define M_PI 3.14159265358979323846

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

typedef struct s_monster
{
	double		x;
	double		y;
	int			alive;
	int			frame;
	double		anim_time;
	double		anim_speed;
	int health;        // Points de vie actuels
	int max_health;    // Points de vie maximum
	int hit_animation; // Pour un effet de clignotement quand touché
	double hit_timer;  // Durée de l'effet de coup
}				t_monster;

typedef struct s_sprite
{
	double		x;
	double		y;
	int			width;
	int			height;
}				t_sprite;

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

	// Frames d'animation des monstres
	t_texture	monster_frames[4];
	int			monster_frame_count;

	char		*monster_paths[4];

	int			ceiling_color;
	int			floor_color;
	int			keys[256];
	int			rotate_left;
	int			rotate_right;
	double		move_speed;
	double		rot_speed;

	// Gestion du temps
	double		last_frame_time;
	double		delta_time;

	// weapon
	t_texture	weapon_tex;
	char		*weapon_paths[4];

	// monsters
	t_monster	monsters[MAX_MONSTERS];
	int			monster_count;
	double		z_buffer[WIN_WIDTH];

	// buffer d'image
	void		*img;
	int			*img_data;
	int			bpp;
	int			size_line;
	int			endian;

	// Pour la souris
	int mouse_x;              // Position actuelle de la souris en X
	int mouse_prev_x;         // Position précédente de la souris en X
	int mouse_enabled;        // Si la rotation par souris est activée
	double mouse_sensitivity; // Sensibilité de la souris

	int firing;                 // Si le joueur est en train de tirer
	double weapon_cooldown;     // Temps entre deux attaques
	double weapon_timer;        // Compteur pour le cooldown
	int weapon_damage;          // Dégâts infligés par l'arme
	double weapon_range;        // Portée de l'arme
	t_texture weapon_frames[4]; // Différentes frames pour l'animation de l'arme
	int weapon_frame_count;     // Nombre de frames d'animation
	int current_weapon_frame;   // Frame actuelle de l'animation
	int weapon_animating;       // Si l'arme est en train de s'animer
	double weapon_anim_time;    // Temps écoulé pour l'animation
	double weapon_anim_speed;   // Vitesse de l'animation

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
	int			hit_type;
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
void			draw_weapon(t_game *game);
int				game_loop(t_game *game);
int				key_release(int keycode, t_game *game);
void			complete_raycasting(t_game *game);
void			handle_movement(t_game *game);
int				mouse_move(int x, int y, t_game *game);
void			toggle_mouse(t_game *game);
int				mouse_click(int button, int x, int y, t_game *game);
void			attack(t_game *game);
int				all_monsters_dead(t_game *game);
void			draw_controls_menu(t_game *game);

// Fonctions pour les monstres
void			init_monsters(t_game *game);
void			render_monsters(t_game *game);

#endif