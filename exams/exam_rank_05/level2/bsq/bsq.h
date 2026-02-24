#ifndef BSQ_H
#define BSQ_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_map
{
	unsigned int height;
	unsigned int width;
	char empty;
	char obstacle;
	char full;
	char **content;
} t_map;

int run_bsq(FILE *file);




#endif