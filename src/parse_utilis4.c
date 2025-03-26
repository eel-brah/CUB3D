/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utilis4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:51:59 by amokhtar          #+#    #+#             */
/*   Updated: 2025/02/15 03:53:05 by eel-brah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../platform.h"

int len_2d(char **sp) {
  int i;

  i = 0;
  while (sp && sp[i])
    i++;
  return (i);
}

bool check_line(char *line) {
  int i;

  i = 0;
  while (line[i] && (line[i + 1] && line[i] != '\n')) {
    if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N' &&
        line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != 'C') {
      return (false);
    }
    i++;
  }
  return (true);
}

void free_map(t_map *map) {
  free(map->no);
  free(map->so);
  free(map->we);
  free(map->ea);
  free(map->map);
  free_linked(map->lst);
  free(map);
}
