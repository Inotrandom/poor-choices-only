#include "engine/cli.h"

int main(int argv, char **argc)
{
	(void)argv;
	(void)argc;

	cli_t cli = cli_t();

	cli.run();

	return 0;
}