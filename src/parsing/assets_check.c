/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:52:34 by ededemog          #+#    #+#             */
/*   Updated: 2025/02/26 21:46:55 by ededemog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int is_valid_texture_file(char *path)
{
    char *trimmed_path;
    int fd;
    int len;
    int result;

    trimmed_path = ft_strtrim(path, " \n\t");
    if (!trimmed_path || !*trimmed_path)
    {
        free(trimmed_path);
        printf("Error: Chemin de texture vide.\n");
        return (0);
    }

    printf("Vérification du chemin : '%s'\n", trimmed_path);
    fd = open(trimmed_path, O_RDONLY);
    if (fd < 0)
    {
        printf("Error: Fichier de texture introuvable : %s\n", trimmed_path);
        free(trimmed_path);
        return (0);
    }

    len = ft_strlen(trimmed_path);
    result = (len >= 4 && ft_strcmp(trimmed_path + len - 4, ".xpm") == 0);
    if (!result)
        printf("Error: Format de texture invalide (uniquement .xpm) : %s\n", trimmed_path);

    close(fd);
    free(trimmed_path);
    return (result);
}

int validate_textures(t_map_info *map_info)
{
    if (!map_info->no_texture || !is_valid_texture_file(map_info->no_texture))
        return (0);
    if (!map_info->so_texture || !is_valid_texture_file(map_info->so_texture))
        return (0);
    if (!map_info->we_texture || !is_valid_texture_file(map_info->we_texture))
        return (0);
    if (!map_info->ea_texture || !is_valid_texture_file(map_info->ea_texture))
        return (0);

    return (1);
}

int process_config_line(t_map_info *map_info, char *line)
{
    char **tokens;

    if (!line || !*line)
        return (1);

    tokens = ft_split(line, ' ');
    if (!tokens)
        return (0);

    if (ft_strcmp(tokens[0], "NO") == 0)
    {
        if (map_info->no_texture)
        {
            printf("Error: Doublon de la texture NO.\n");
            free_tokens(tokens);
            return (0);
        }
        map_info->no_texture = ft_strdup(tokens[1]);
    }
    else if (ft_strcmp(tokens[0], "SO") == 0)
    {
        if (map_info->so_texture)
        {
            printf("Error: Doublon de la texture SO.\n");
            free_tokens(tokens);
            return (0);
        }
        map_info->so_texture = ft_strdup(tokens[1]);
    }
    else if (ft_strcmp(tokens[0], "WE") == 0)
    {
        if (map_info->we_texture)
        {
            printf("Error: Doublon de la texture WE.\n");
            free_tokens(tokens);
            return (0);
        }
        map_info->we_texture = ft_strdup(tokens[1]);
    }
    else if (ft_strcmp(tokens[0], "EA") == 0)
    {
        if (map_info->ea_texture)
        {
            printf("Error: Doublon de la texture EA.\n");
            free_tokens(tokens);
            return (0);
        }
        map_info->ea_texture = ft_strdup(tokens[1]);
    }

    free_tokens(tokens);
    return (1);
}