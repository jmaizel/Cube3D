/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdedessu <cdedessu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:37:18 by jmaizel           #+#    #+#             */
/*   Updated: 2025/04/27 16:29:56 by cdedessu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Point d'entrée principal du programme */
int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
        return (exit_error("Usage: ./cub3D map.cub"), 1);
    
    // Initialisation des variables
    ft_memset(&game, 0, sizeof(t_game));
    game.rotate_left = 0;
    game.rotate_right = 0;
    game.move_speed = 0.13;
    game.rot_speed = 0.03;
    game.monster_frame_count = 0;
    game.last_frame_time = 0.0;
    game.delta_time = 0.0;
	game.mouse_enabled = 0;
    game.mouse_sensitivity = 0.002; // Ajustez selon vos préférences
    game.mouse_x = WIN_WIDTH / 2;
    game.mouse_prev_x = WIN_WIDTH / 2;
	game.firing = 0;
    game.weapon_cooldown = 0.5;  // Une attaque toutes les 0.5 secondes
    game.weapon_timer = 0.0;
    game.weapon_damage = 25;     // 4 coups pour tuer un monstre avec 100PV
    game.weapon_range = 3.0;     // Porté d'attaque de 3 unités
    
    // Parsing et initialisation
    if (!parse_cub_file(argv[1], &game))
        return (1);

    init_monsters(&game);
    
    // Initialisation de la MLX
    game.mlx = mlx_init();
    if (!game.mlx)
        return (exit_error("Erreur init MLX"), 1);
    
    // Chargement des textures
    if (!load_all_textures(&game))
        return (1);
    
    // Création de la fenêtre
    game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT,
            "Cub3D avec raycasting");
    if (!game.win)
        return (exit_error("Erreur fenêtre"), 1);
    
    // Création de l'image
    game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
    game.img_data = (int *)mlx_get_data_addr(game.img, &game.bpp,
            &game.size_line, &game.endian);
    
    // Première frame
    render_frame(&game);
    mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
    
    // Configuration des hooks
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_mouse_hook(game.win, mouse_click, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    
    // Lancement de la boucle principale
    mlx_loop(game.mlx);
    
    return (0);
}