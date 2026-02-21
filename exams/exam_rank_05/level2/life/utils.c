#include "life.h"

void free_rows(t_game *g, int nrows)
{
	if (nrows == -1)
		nrows = g->h;
	for (int i = 0; i < nrows; i++)
		free(g->board[i]);
	free(g->board);

}

void print_board(t_game *g)
{
	int putspace;

	for (int i = 0; i < g->h; i++)
	{
		putspace = 0;
		for (int j = 0; j < g->w; j++)
		{
			if (g->board[i][j] == ' ')
			{
				if (putspace)
					putchar(' ');
				while(g->board[i][j] == ' ')
					j++;
				j--;
			}
			else
			{
				putspace = 1;
				putchar(g->board[i][j]);
			}
		}
		putchar('\n');
	}
}

