#include "life.h"

static int neighbours(t_game *g, char **tmp, int current_i, int current_j)
{
	int ni, nj;
	int total = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
				continue;
			ni = current_i + i;
			nj = current_j + j;
			if (ni < 0 || ni >= g->h || nj < 0 || nj >= g->w)
				continue;
			if (tmp[ni][nj] == 'O')
				total++;
		}
	}
	return (total);
}


int life(t_game *g)
{

	char **tmp = (char **) malloc((sizeof(char *) * (g->h + 1)));
	if (!tmp)
		return (0);
	tmp[g->h] = 0;
	for (int i = 0; i < g->h; i++)
	{
		tmp[i] = malloc(sizeof(char) * (g->w +1));
		if (!(tmp[i]))
		{
			free_rows(g, i);
			return (0);
		}
		for (int k = 0; k < g->w ; k++)
			tmp[i][k] = ' ';
		tmp[i][g->w] = 0;
	}
	// // // // // // //
	
	for (int iter = 0; iter < g->it ; iter++)
	{
		// printf("%d, ", iter);
		for  (int i = 0; i < g->h ; i++)
		{
			for (int j = 0; j < g->w; j++)
			{
				tmp[i][j] = g->board[i][j];
			}
		}
		for  (int i = 0; i < g->h ; i++)
		{
			for (int j = 0; j < g->w; j++)
			{
				char current = tmp[i][j];
				int n = neighbours(g, tmp, i, j);
				if (current == 'O' && (n == 2 || n== 3))
					g->board[i][j] = 'O';
				else if (current == ' ' && (n== 3))
					g->board[i][j] = 'O';
				else
					g->board[i][j] = ' ';
			}
		}
	}


	for (int i = 0; i < g->h; i++)
	{
		free(tmp[i]);
	}
	free(tmp);

	return (1);
}
