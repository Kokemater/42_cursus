#include "bsq.h"

int is_printable(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void print_map(t_map *map)
{
	printf("height : %d \n", map->height);
	printf("width : %d \n", map->width);
	printf("empty : '%c' \n", map->empty);	
	printf("obstacle : '%c' \n", map->obstacle);
	printf("full : '%c' \n", map->full);

	for (unsigned int i = 0; i < map->height; i++)
	{
		printf("%s$\n", map->content[i]);
	}
	// unsigned int height;
	// unsigned int width;
	// char empty;
	// char obstacle;
	// char full;
	// char **content;
}

int read_header(FILE *file, t_map *map)
{
	int r;
	
	r = fscanf(file, "%d %c %c %c", &map->height, &map->empty, &map->obstacle, &map->full);
	if (r != 4)
		return (-1);
	if (!is_printable(map->empty) || !is_printable(map->obstacle) || !is_printable(map->full))
		return (-1);
	return (1);	
}

static void free_content(t_map *map, unsigned int filled)
{
    for (unsigned int i = 0; i < filled; i++)
        free(map->content[i]);
    free(map->content);
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void free_content(t_map *map, unsigned int filled)
{
    for (unsigned int i = 0; i < filled; i++)
        free(map->content[i]);
    free(map->content);
}


int read_map(FILE *file, t_map *map)
{
    size_t cap = 0;
    ssize_t r;
    unsigned int i;

    map->content = malloc((map->height + 1) * sizeof(char *));
    if (!map->content)
        return (-1);

    map->content[map->height] = NULL;

    for (i = 0; i < map->height; i++)
    {
        map->content[i] = NULL;

        r = getline(&map->content[i], &cap, file);
        if (r == -1)
        {
            free_content(map, i);
            return (-1);
        }

        /* Remove newline */
        if (r > 0 && map->content[i][r - 1] == '\n')
        {
            map->content[i][r - 1] = '\0';
            r--;
        }

        /* Remove carriage return (Windows CRLF protection) */
        if (r > 0 && map->content[i][r - 1] == '\r')
        {
            map->content[i][r - 1] = '\0';
            r--;
        }

        if (i == 0)
        {
            if (r == 0)   // empty first line is invalid
            {
                free_content(map, i + 1);
                return (-1);
            }
            map->width = (unsigned int)r;
        }
        else
        {
            if ((unsigned int)r != map->width)
            {
                free_content(map, i + 1);
                return (-1);
            }
        }
    }

    return (0);
}



int run_bsq(FILE *file)
{
	t_map map;
	if (read_header(file, &map) == -1)
		return (-1);
	if (read_map(file, &map) == -1)
		return (-1);
	print_map(&map);
	return (1);
}