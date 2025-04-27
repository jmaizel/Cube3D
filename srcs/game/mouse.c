/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:46:34 by cdedessu          #+#    #+#             */
/*   Updated: 2025/04/27 16:52:10 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Fonction mouse_move modifiée
int mouse_move(int x, int y, t_game *game)
{
    if (!game->mouse_enabled)
        return (0);
    
    // Ignorer les mouvements verticaux (y)
    (void)y;
    
    // Enregistrer la position actuelle
    game->mouse_prev_x = game->mouse_x;
    game->mouse_x = x;
    
    // Calculer le déplacement
    int delta_x = game->mouse_x - game->mouse_prev_x;
    
    // Appliquer la rotation
    if (delta_x != 0)
    {
        double rotation_angle = delta_x * game->mouse_sensitivity;
        
        // Rotation similaire à rotate_left et rotate_right
        double old_dir_x = game->player.dir_x;
        double old_plane_x = game->player.plane_x;
        
        game->player.dir_x = game->player.dir_x * cos(rotation_angle) - 
                            game->player.dir_y * sin(rotation_angle);
        game->player.dir_y = old_dir_x * sin(rotation_angle) + 
                            game->player.dir_y * cos(rotation_angle);
        game->player.plane_x = game->player.plane_x * cos(rotation_angle) - 
                               game->player.plane_y * sin(rotation_angle);
        game->player.plane_y = old_plane_x * sin(rotation_angle) + 
                               game->player.plane_y * cos(rotation_angle);
        
        // Recentrer la souris si elle s'approche trop des bords
        if (game->mouse_x < 100 || game->mouse_x > WIN_WIDTH - 100)
        {
            game->mouse_x = WIN_WIDTH / 2;
            game->mouse_prev_x = WIN_WIDTH / 2;
            mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
        }
    }
    
    return (0);
}

// Fonction toggle_mouse modifiée
void toggle_mouse(t_game *game)
{
    game->mouse_enabled = !game->mouse_enabled;
    
    if (game->mouse_enabled)
    {
        // Masquer le curseur et le centrer
        mlx_mouse_hide(game->mlx, game->win);
        mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
        game->mouse_x = WIN_WIDTH / 2;
        game->mouse_prev_x = WIN_WIDTH / 2;
    }
    else
    {
        // Afficher le curseur
        mlx_mouse_show(game->mlx, game->win);
    }
}
void attack(t_game *game)
{
    int i;
    double distance;
    double dx, dy;
    
    // Vérifier si l'arme est prête
    if (game->weapon_timer > 0)
        return;
    
    game->firing = 1;
    game->weapon_timer = game->weapon_cooldown;
    
    // Parcourir tous les monstres
    for (i = 0; i < game->monster_count; i++)
    {
        if (!game->monsters[i].alive)
            continue;
        
        // Calculer la distance au monstre
        dx = game->monsters[i].x - game->player.x;
        dy = game->monsters[i].y - game->player.y;
        distance = sqrt(dx * dx + dy * dy);
        
        if (distance > game->weapon_range)
            continue;  // Trop loin
        
        // Calculer l'angle vers le monstre
        double angle = atan2(dy, dx);
        
        // Angle du joueur
        double player_angle = atan2(game->player.dir_y, game->player.dir_x);
        
        // Normaliser les angles entre -PI et PI
        while (angle > M_PI) angle -= 2 * M_PI;
        while (angle < -M_PI) angle += 2 * M_PI;
        while (player_angle > M_PI) player_angle -= 2 * M_PI;
        while (player_angle < -M_PI) player_angle += 2 * M_PI;
        
        // Calculer la différence d'angle
        double angle_diff = fabs(angle - player_angle);
        while (angle_diff > M_PI) angle_diff = 2 * M_PI - angle_diff;
        
        // Vérifier si le monstre est dans le champ de vision (60 degrés)
        if (angle_diff < (M_PI / 3))  // 60 degrés = PI/3 radians
        {
            // Touché! Réduire la santé du monstre
            game->monsters[i].health -= game->weapon_damage;
            
            // Activer l'animation de coup
            game->monsters[i].hit_animation = 1;
            game->monsters[i].hit_timer = 0.2;  // 0.2 secondes d'effet
            
            // Vérifier si le monstre est mort
            if (game->monsters[i].health <= 0)
            {
                game->monsters[i].alive = 0;
                
                // Éventuellement jouer un son ou ajouter un effet
                ft_printf("Monstre %d tué!\n", i);
            }
        }
    }
}

int mouse_click(int button, int x, int y, t_game *game)
{
    (void)x;
    (void)y;
    
    if (button == 1)  // Clic gauche
    {
        attack(game);
    }
    
    return (0);
}