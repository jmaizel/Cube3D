/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaizel <jmaizel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:45:10 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/30 14:39:48 by jmaizel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

/* Vérifie si une position sur la map est valide (pas de mur ni hors limites) */
int is_valid_position(t_game *game, double x, double y)
{
    if (x < 0 || y < 0 || (int)x >= game->map.width
        || (int)y >= game->map.height)
        return (0);
    if (game->map.grid[(int)y][(int)x] == '1')
        return (0);
    // Vérifier si c'est une porte fermée
    if (game->map.grid[(int)y][(int)x] == 'D' && !game->door_opened)
        return (0);
    return (1);
}

/* Déplace le joueur vers l'avant */
void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * game->move_speed;
	new_y = game->player.y + game->player.dir_y * game->move_speed;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers l'arrière */
void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers la gauche */
void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Déplace le joueur vers la droite */
void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (is_valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (is_valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

/* Fait pivoter le joueur vers la gauche */
void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y
		* cos(-ROT_SPEED);
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED)
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y
		* cos(-ROT_SPEED);
}

/* Fait pivoter le joueur vers la droite */
void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y
		* cos(ROT_SPEED);
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED)
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y
		* cos(ROT_SPEED);
}

/* Gère l'appui sur une touche */
int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 1;
	if (keycode == 65361 || keycode == 123) // Flèche gauche
		game->rotate_left = 1;
	else if (keycode == 65363 || keycode == 124) // Flèche droite
		game->rotate_right = 1;
	else if (keycode == 65307 || keycode == 53) // ESC key
		close_window(game);
	else if (keycode == 109 || keycode == 46) // Touche M
		toggle_mouse(game);
	else if (keycode == 32 || keycode == 1) // Touche espace ou clic gauche
		attack(game);
		
	return (0);
}

/* Gère le relâchement d'une touche */
int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->keys[keycode] = 0;
	if (keycode == 65361 || keycode == 123)
		game->rotate_left = 0;
	else if (keycode == 65363 || keycode == 124)
		game->rotate_right = 0;
	return (0);
}

/* Gère tous les mouvements actifs du joueur */
void	handle_movement(t_game *game)
{
	if (game->keys[119] || game->keys[13])
		move_forward(game);
	if (game->keys[115] || game->keys[1])
		move_backward(game);
	if (game->keys[97] || game->keys[0])
		move_left(game);
	if (game->keys[100] || game->keys[2])
		move_right(game);
	if (game->rotate_left)
		rotate_left(game);
	if (game->rotate_right)
		rotate_right(game);
}
double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	update_monster_animations(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->monster_count)
	{
		if (game->monsters[i].alive)
		{
			// Ajouter le temps écoulé
			game->monsters[i].anim_time += game->delta_time;
				// Utilise game->delta_time
			// Changer de frame si nécessaire
			if (game->monsters[i].anim_time >= game->monsters[i].anim_speed)
			{
				game->monsters[i].anim_time -= game->monsters[i].anim_speed;
				game->monsters[i].frame = (game->monsters[i].frame + 1)
					% game->monster_frame_count;
			}
		}
		i++;
	}
}

/* boucle principale du jeu */
int game_loop(t_game *game)
{
    double current_time;

    // Calculer le delta time
    current_time = get_time();
    if (game->last_frame_time == 0.0)
        game->last_frame_time = current_time;
    game->delta_time = current_time - game->last_frame_time;
    game->last_frame_time = current_time;

    // Limiter le delta time pour éviter les sauts lors de freezes
    if (game->delta_time > 0.1)
        game->delta_time = 0.1;

    // Mettre à jour le timer de l'arme
    if (game->weapon_timer > 0)
    {
        game->weapon_timer -= game->delta_time;
        if (game->weapon_timer <= 0)
        {
            game->weapon_timer = 0;
            game->firing = 0;
        }
    }

    // Mettre à jour l'animation de l'arme
    if (game->weapon_animating)
    {
        game->weapon_anim_time += game->delta_time;

        // Avancer l'animation
        if (game->weapon_anim_time >= game->weapon_anim_speed)
        {
            game->weapon_anim_time -= game->weapon_anim_speed;
            game->current_weapon_frame++;

            // Vérifier si l'animation est terminée
            if (game->current_weapon_frame >= game->weapon_frame_count)
            {
                game->current_weapon_frame = 0;
                game->weapon_animating = 0;
            }
        }
    }

    // Mettre à jour les effets de coup pour les monstres
    for (int i = 0; i < game->monster_count; i++)
    {
        if (game->monsters[i].hit_timer > 0)
        {
            game->monsters[i].hit_timer -= game->delta_time;
            if (game->monsters[i].hit_timer <= 0)
            {
                game->monsters[i].hit_timer = 0;
                game->monsters[i].hit_animation = 0;
            }
        }
    }

    // Mise à jour des animations des monstres
    update_monster_animations(game);

    // Vérifier si tous les monstres sont morts pour ouvrir la porte
    if (!game->all_monsters_killed && all_monsters_dead(game))
    {
        game->all_monsters_killed = 1;
        game->door_opened = 1;
        game->victory_timer = 3.0; // Afficher le message pendant 3 secondes
        game->victory_displayed = 1;
        ft_printf("Tous les monstres ont été éliminés! La porte est ouverte!\n");
    }

    // Vérifier si le joueur a traversé la porte pour terminer le jeu
    if (game->door_opened && game->victory_displayed != 2)
    {
        // Trouver la position de la porte
        int door_found = 0;
        int door_x = 0;
        int door_y = 0;
        
        for (int y = 0; y < game->map.height && !door_found; y++)
        {
            for (int x = 0; x < (int)ft_strlen(game->map.grid[y]) && !door_found; x++)
            {
                if (game->map.grid[y][x] == 'D')
                {
                    door_x = x;
                    door_y = y;
                    door_found = 1;
                }
            }
        }
        
        if (door_found)
        {
            // Calculer la distance entre le joueur et la porte
            double dx = game->player.x - (door_x + 0.5);
            double dy = game->player.y - (door_y + 0.5);
            double distance = sqrt(dx * dx + dy * dy);
            
            // Si le joueur est assez proche de la porte
            if (distance < 1.0)
            {
                // Afficher le message de victoire une seule fois
                ft_printf("VICTOIRE! Vous avez traversé la porte et terminé le jeu!\n");
                
                // Rendre une dernière frame avec le message de victoire
                game->victory_displayed = 2;
                render_frame(game);
                mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
                
                // Afficher le message de victoire finale
                int msg_x = WIN_WIDTH / 2 - 200;
                int msg_y = WIN_HEIGHT / 2;
                mlx_string_put(game->mlx, game->win, msg_x, msg_y - 40, 0xFFFF00,
                    "FÉLICITATIONS!");
                mlx_string_put(game->mlx, game->win, msg_x, msg_y, 0xFFFF00,
                    "VOUS AVEZ TERMINÉ LE JEU!");
                
                // Attendre un court instant pour que le message soit visible
                usleep(2000000); // 2 secondes
                
                // Fermer le jeu
                close_window(game);
                return (0);
            }
        }
    }

    // Gestion du timer pour le message de victoire
    if (game->victory_timer > 0)
    {
        game->victory_timer -= game->delta_time;
        
        if (game->victory_timer <= 0)
        {
            game->victory_timer = 0;
            if (game->victory_displayed == 1)
                game->victory_displayed = 0;
        }
    }

    // Gérer les mouvements du joueur
    handle_movement(game);

    // Générer la nouvelle frame
    render_frame(game);

    // Afficher la frame
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

    draw_controls_menu(game);

    // Limiter le framerate à environ 60 FPS
    usleep(16000);

    return (0);
}