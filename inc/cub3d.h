/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:54 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/02 14:39:43 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

/*
** Constantes
*/
# define ESC 65307
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define X 0
# define Y 1
# define IMG_SIZE 64
# define P_SPEED 0.03
# define R_SPEED 0.04
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

/*
** Structures
*/
typedef struct s_img
{
	void	*img_mlx;
	int		*addr;
	int		line_length;
	int		bits_per_pixel;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_map_info
{
	/* Données de base de la map */
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*sprite;
	int		floor_color;
	int		ceiling_color;
	int		map_height;
	int		map_width;

	/* Position du joueur */
	int		player_x;
	int		player_y;
	char	player_dir;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	/* Données de raycasting */
	double	pos[2];
	double	dir[2];
	double	plane[2];
	int		map_p[2];
	double	camerax[2];
	double	ray_dir[2];
	double	side_dist[2];
	double	ddist[2];
	int		step[2];
	int		wall_x;
	int		tex[2];
	int		hit;
	int		side;
	double	wall_dist;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		tex_num;
	int		tex_step;
	int		tex_pos;
	int		color;
	int		y;

	/* MLX et textures */
	void	*mlx;
	void	*win;
	int		**assets;
	t_img	*img;

	/* Mouvement */
	int		move[2];
	int		moved;
	int		rot_left;
	int		rot_right;
}			t_map_info;

/*
** Main
*/
int			close_window(t_map_info *map_info);
int			key_hook(int keycode, t_map_info *map_info);

/*
** Parsing du fichier
*/
int			is_valid_map_file(char *filename);
int			read_map_file(t_map_info *map_info, char *file_path);
int			parse_config(t_map_info *map_info);

/*
** Parsing des éléments
*/
void		parse_resolution(t_map_info *map_info, char *line);
int			parse_texture(char **texture, char *line, char *identifier);
int			parse_color(int *color, char *line, char *identifier);
int			is_map_line(char *line);
void		parse_map_only(t_map_info *map_info);

/*
** Validation de la map
*/
int			check_required_elements(t_map_info *map_info);
int			check_color_format(char *line, char *identifier);
int			is_valid_texture_file(char *path);
int			validate_textures(t_map_info *map_info);
int			validate_map(t_map_info *map_info);
void		detect_player(t_map_info *map_info);

/*
** Utilitaires
*/
void		free_map(char **map);
void		free_tokens(char **tokens);
void		free_all(t_map_info *map_info);
void		free_game(t_map_info *map_info);
void		free_tex(t_map_info *map_info);
void		delete_mlx(t_map_info *map_info);
void		error_exit(t_map_info *map_info, char *message);

/*
** Rendering et raycasting
*/
void		draw_square(t_map_info *map_info, int x, int y, int color);
void		render_map(t_map_info *map_info);
int			**init_buff(t_map_info *map_info);
void		init_ray(t_map_info *map_info, int x);
void		step_sidedist(t_map_info *map_info);
void		algo_dda(t_map_info *map_info);
void		calc_dist(t_map_info *map_info);
void		raycasting(t_map_info *map_info);

/*
** Initialisation
*/
void		init_mlx(t_map_info *map_info);
void		set_img(t_img *img);
void		map_pos(t_map_info *map_info);
void		xpm_to_img(t_map_info *map_info, t_img *img, char *tex);
void		init_textures(t_map_info *map_info);
void		launch_game(t_map_info *map_info);

/*
** Mouvement
*/
int			move(t_map_info *map_info);
int			left_rotate(t_map_info *map_info);
int			right_rotate(t_map_info *map_info);
int			can_move(t_map_info *map_info, double x, double y);
int			y_move(t_map_info *map_info, int down_up);
int			x_move(t_map_info *map_info, int left_right);
int			moves(t_map_info *map_info);
int			destroy_game(t_map_info *map_info);
int			key_release(int keycode, t_map_info *map_info);

#endif