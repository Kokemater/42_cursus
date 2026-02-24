

#include "bsq.h"

int main(int argc, char **argv)
{

	if (argc == 1)
	{
		if (run_bsq(stdin) == -1)
			fprintf(stderr, "map error");
	}
	else
	{
		FILE *file;

		for (int i = 1; i < argc; i++)
		{
			file = fopen(argv[i], "r");
			if (!file)
				fprintf(stderr, "map error");
			if (run_bsq(file) == -1)
			fprintf(stderr, "map error");
			fprintf(stdout, "\n");
		}
	}
	
}