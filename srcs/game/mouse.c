/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:46:34 by cdedessu          #+#    #+#             */
/*   Updated: 2025/04/27 16:15:59 by cdedessu         ###   ########.fr       */
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