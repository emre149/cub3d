/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:54 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/26 21:44:28 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# define ESC 65307
# define MINI_MAP_SCALE 5

typedef struct s_data
{
	void	*mlx;
	void	*win;
}			t_data;

typedef struct s_map_info
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*sprite;
	int		floor_color;
	int		ceiling_color;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		map_height;
	int		map_width;
}			t_map_info;

// main
int			close_window(t_data *data);
int			key_hook(int keycode, t_data *data);

// parsing

int			parse_config(t_map_info *map_info);
void		parse_color(int *color, char *line);
void		parse_texture(char **texture, char *line);
void		parse_resolution(t_map_info *map_info, char *line);
void 		detect_player(t_map_info *map_info);


int			is_map_line(char *line);
void		parse_map_only(t_map_info *map_info);

int			read_map_file(t_map_info *map_info, char *file_path);
int			is_valid_map_file(char *filename);

// parsing utils

void		free_map(char **map);
void		free_tokens(char **tokens);

// rendering

void	draw_square(t_data *data, int x, int y, int color);
void	render_map(t_data *data, t_map_info *map_info);

// parsing validation

int is_valid_texture_file(char *path);
int validate_textures(t_map_info *map_info);

#endif