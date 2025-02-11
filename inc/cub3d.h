/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:54 by ededemog          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/11 15:59:40 by ededemog         ###   ########.fr       */
=======
/*   Updated: 2025/02/07 16:43:17 by ededemog         ###   ########.fr       */
>>>>>>> 1846e4ad457c65975e64a6830ee988060fee7323
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

typedef struct s_data
{
	void	*mlx;
	void	*win;
}			t_data;

typedef struct s_map_info
{
	char	**map;
<<<<<<< HEAD
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*sprite;
	int		floor_color;
=======
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	floor_color;
>>>>>>> 1846e4ad457c65975e64a6830ee988060fee7323
	int		ceiling_color;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		map_height;
	int		map_width;
}			t_map_info;

<<<<<<< HEAD
// main
int	close_window(t_data *data);
int	key_hook(int keycode, t_data *data);

// parsing
int	parse_config(t_map_info *map_info);
void	parse_map_only(t_map_info *map_info);
int	read_map_file(t_map_info *map_info, char *file_path);
int	is_valid_map_file(char *filename);
int is_map_line(char *line);

// parsing utils

void	free_map(char **map);

=======
// parsing

int			parse_color(char *line);
int			parse_map_file(t_map_info *map_info, char *file_path);
int			read_map(t_map_info *map_info, int fd);
int			valid_map(t_map_info *map_info);
int			validate_textures(t_map_info *map_info);

// parsing utils
int			ft_isspace_str(char *str);
void		*ft_realloc(void *ptr, size_t size);
void		free_map(char **map);
void		free_map_info(t_map_info *map_info);
>>>>>>> 1846e4ad457c65975e64a6830ee988060fee7323

#endif