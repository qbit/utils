#include <err.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int ch;
	char *c;
	while ((ch = getopt(argc, argv, "p:")) != -1) {
		switch(ch) {
		case 'p':
			c = optarg;
			break;
		}
		argc -= optind;
		argv += optind;
        }

	if (pledge(NULL, c) == -1)
		err(1, "pledge");

	execvp(argv[0], argv);
}
