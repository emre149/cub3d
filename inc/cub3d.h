/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:19:54 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/07 16:43:17 by ededemog         ###   ########.fr       */
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
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	floor_color;
	int		ceiling_color;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		map_height;
	int		map_width;
}			t_map_info;

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

#endif