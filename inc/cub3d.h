/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:36:48 by ededemog          #+#    #+#             */
/*   Updated: 2025/03/18 17:31:29 by ededemog         ###   ########.fr       */
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
** ========================== CONSTANTS ==========================
*/

/* Keys */
# define ESC 65307

/* Directions and textures */
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define DOOR 4
# define X 0
# define Y 1

/* Game settings */
# define IMG_SIZE 64
# define P_SPEED 0.03
# define R_SPEED 0.04
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MINI_MAP_SCALE 10
# define DOOR_OPEN 'D'
# define DOOR_CLOSE 'd'

/*
** ========================== STRUCTURES ==========================
*/

/* Graphics */
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

/* Mouse */
typedef struct s_mouse
{
	int		prev_x;
	int		x;
	int		y;
	int		is_captured;
	int		moved;
}			t_mouse;

/* Drawing utilities */
typedef struct s_line_params
{
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
}			t_line_params;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_draw_data
{
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}			t_draw_data;

/* Main game data - contains map properties, player data, raycasting info,
	graphics, doors and input */
typedef struct s_map_info
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*sprite;
	char	*door_text;
	int		floor_color;
	int		ceiling_color;
	int		map_height;
	int		map_width;

	int		player_x;
	int		player_y;
	char	player_dir;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move[2];
	int		moved;
	int		rot_left;
	int		rot_right;
	double	rot_speed;

	double	pos[2];
	double	dir[2];
	double	plane[2];
	int		map_p[2];
	double	camerax[2];
	double	ray_dir[2];
	double	side_dist[2];
	double	ddist[2];
	int		step[2];
	int		hit;
	int		side;
	double	wall_dist;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		tex_num;
	int		wall_x;
	int		tex[2];
	int		tex_step;
	int		tex_pos;
	int		color;
	int		y;

	void	*mlx;
	void	*win;
	int		**assets;
	t_img	*img;

	int		door_state[1000][2];
	int		door_count;
	double	door_timer[1000];

	t_mouse	mouse;
}			t_map_info;

/*
** ========================== FUNCTION PROTOTYPES ==========================
*/

/*
** Core game functions
*/
int			close_window(t_map_info *map_info);
int			key_hook(int keycode, t_map_info *map_info);
int			render_frame(void *param);
int			destroy_game(t_map_info *map_info);
int			key_release(int keycode, t_map_info *map_info);

/*
** Initialization
*/
void		init_mlx(t_map_info *map_info);
void		set_img(t_img *img);
void		map_pos(t_map_info *map_info);
void		xpm_to_img(t_map_info *map_info, t_img *img, char *tex);
void		init_textures(t_map_info *map_info);
void		launch_game(t_map_info *map_info);
void		init_doors(t_map_info *map_info);
void		init_mouse_controls(t_map_info *data);

/*
** File parsing
*/
int			is_valid_map_file(char *filename);
int			read_map_file(t_map_info *map_info, char *file_path);
int			parse_config(t_map_info *map_info);
int			process_config_line(t_map_info *map_info, char *line,
				int *map_started);
int			process_texture_line(t_map_info *map_info, char *line);
int			process_color_line(t_map_info *map_info, char *line);
int			process_map_line(char *line, int *map_started);

/*
** Element parsing
*/
void		parse_resolution(t_map_info *map_info, char *line);
int			parse_texture(char **texture, char *line, char *identifier);
int			parse_color(int *color, char *line, char *identifier);
int			is_map_line(char *line);
void		parse_map_only(t_map_info *map_info);

/*
** Validation
*/
int			validate_textures(t_map_info *map_info);
int			check_elements(t_map_info *map_info);
int			check_color_format(char *line, char *identifier);
int			is_valid_texture_file(char *path);
int			validate_map(t_map_info *map_info);
void		detect_player(t_map_info *map_info);
void		set_directions(int directions[8][2]);

/*
** Map utilities
*/
int			get_map_bounds(char **map, int *start, int *end);
char		**duplicate_map_lines(char **map, int start, int end);
int			check_valid_chars(char **map);
int			is_empty_or_edge(char **map, int i, int j);
int			check_map_closed(char **map);
int			is_surrounded(char **map, int i, int j);

/*
** Player initialization
*/
void		normalize_map(char **map, t_map_info *map_info);
void		restore_player(t_map_info *map_info);
void		init_player_direction(t_map_info *map_info);
void		set_player_ns_direction(t_map_info *map_info);
void		set_player_ew_direction(t_map_info *map_info);

/*
** Memory management
*/
void		free_map(char **map);
void		free_tokens(char **tokens);
void		free_all(t_map_info *map_info);
void		free_game(t_map_info *map_info);
void		free_tex(t_map_info *map_info);
void		delete_mlx(t_map_info *map_info);
void		error_exit(t_map_info *map_info, char *message);

/*
** Rendering
*/
void		draw_square(t_map_info *map_info, int x, int y, int color);
void		render_map(t_map_info *map_info);
int			**init_buff(t_map_info *map_info);
void		raycasting(t_map_info *map_info);
void		draw_line(t_map_info *map_info, int **buff, int x);

/*
** Raycasting
*/
void		init_ray(t_map_info *map_info, int x);
void		step_sidedist(t_map_info *map_info);
void		algo_dda(t_map_info *map_info);
void		calc_dist(t_map_info *map_info);

/*
** Movement
*/
int			move(t_map_info *map_info);
int			left_rotate(t_map_info *map_info);
int			right_rotate(t_map_info *map_info);
int			can_move(t_map_info *map_info, double x, double y);
int			y_move(t_map_info *map_info, int down_up);
int			x_move(t_map_info *map_info, int left_right);
int			moves(t_map_info *map_info);
int			handle_mouse_move(int x, int y, void *param);
int			toggle_mouse_capture(int keycode, void *param);

/*
** Minimap
*/
void		draw_mini_map(t_map_info *data, t_map_info *map_info);
void		draw_line_minimap(t_map_info *data, t_point start, t_point end,
				int color);
void		draw_player_dir(t_map_info *data, t_map_info *map_info);
void		draw_player_dot(t_map_info *data, int player_x, int player_y);

/*
** Door functionality
*/
int			is_door(t_map_info *map_info, int x, int y);
int			is_door_closed(t_map_info *map_info, int x, int y);
int			find_door_index(t_map_info *map_info, int x, int y);
void		toggle_door(t_map_info *map_info, int x, int y);
void		interact_with_door(t_map_info *map_info);

#endif