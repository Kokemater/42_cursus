#ifndef LIFE_H
#define LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_game
{
	int w;
	int h;
	int it;
	int y;
	int x;
	int write;
	char **board;
} t_game;

int init_board(t_game *g);
int parse_args(t_game *g, int argc, char **argv);
void print_board(t_game *g);
int life(t_game *g);

void draw_board(t_game *g);
void free_rows(t_game *g, int nrows);

#endif