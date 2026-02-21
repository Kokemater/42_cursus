#include "life.h"

int parse_args(t_game *g, int argc, char **argv)
{
	if (argc != 4)
		return (0);
	g->w = atoi(argv[1]);
	g->h = atoi(argv[2]);
	g->it = atoi(argv[3]);
	if (g->w < 0 || g->h < 0 || g->it < 0)
		return (0);
	return (1);
}

int init_board(t_game *g)
{
	g->board = (char **) malloc((sizeof(char *) * (g->h + 1)));
	if (!g->board)
		return (0);
	g->board[g->h] = 0;
	for (int i = 0; i < g->h; i++)
	{
		g->board[i] = malloc(sizeof(char) * (g->w +1));
		if (!(g->board[i]))
		{
			free_rows(g, i);
			return (0);
		}
		for (int k = 0; k < g->w ; k++)
			g->board[i][k] = ' ';
		g->board[i][g->w] = 0;
	}
	return (1);
}

void draw_board(t_game *g)
{
	char c;
	int i = 0;
	int j = 0;
	g->write = 0;
	while(read(0, &c, 1) == 1)
	{
		if (c == 'w' && i > 0)
			i -= 1;
		else if (c == 's' && i < (g->h -1))
			i += 1;
		else if (c == 'a' && j > 0)
			j -= 1;
		else if (c == 'd' && j < (g->w -1))
			j += 1;
		else if (c == 'x')
		{
			if (g->write == 1) g->write = 0;
			else g->write  = 1;
		}
		else
			continue;
		
		if (g->write == 1)
			g->board[i][j] = 'O';
	}
}