/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thchau <thchau@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 19:52:31 by thchau            #+#    #+#             */
/*   Updated: 2026/03/30 16:39:01 by thchau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

int		parse_map(t_game *game, char **lines, int line_count);
int		validate_map(t_game *game);
int		validate_elements(t_game *game);
bool	is_map_line(char *line);
int		parse_colors(t_game *game, char **lines, int line_count);
int		set_rgb_line(int *field, const char *line);
int		parse_textures(t_game *game, char **lines, int line_count);
int		find_player(t_game *game);
#endif