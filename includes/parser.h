/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 19:52:31 by thchau            #+#    #+#             */
/*   Updated: 2026/03/26 20:42:22 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

// Main parser function
int	parse_file(t_game *game, const char *filename);

// Map parsing
int	parse_map(t_game *game, char **lines, int line_count);
int	validate_map(t_game *game);

// Color parsing
int	parse_colors(t_game *game, const char *floor_line, const char *ceiling_line);

// Texture parsing
int	parse_textures(t_game *game, char **lines, int line_count);

#endif