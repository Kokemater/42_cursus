#include "life.h"

int main(int argc, char **argv)
{
	t_game g;

	if (!(parse_args(&g, argc, argv)))
		return (1);
	if (!(init_board(&g)))
		return (1);
	draw_board(&g);
	if (!life(&g))
		return (1);
	print_board(&g);
	free_rows(&g, -1);
	return (0);
}