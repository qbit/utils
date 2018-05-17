#include <err.h>
#include <fcntl.h>
#include <machine/apmvar.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1

int
main(int argc, char **argv)
{
	int apmfd, ch;
	int cr = TRUE;
	int state = FALSE;
	struct apm_power_info info;
	while ((ch = getopt(argc, argv, "bhln")) != -1) {
		switch(ch) {
		case 'l':
			state = TRUE;
			break;
		case 'n':
			cr = FALSE;
			break;
		case 'h':
			printf("Usage: [lnh]\n");
			return 0;
		}
	}

	apmfd = open("/dev/apm", O_RDONLY);
	ioctl(apmfd, APM_IOC_GETPOWER, &info);

	if (pledge("stdio rpath wpath cpath", NULL) == -1)
		err(1, "pledge");

	if (cr)
		printf("%s%d\n", (info.ac_state == 0 && state == TRUE) ? "-" : "", info.battery_life);
	else
		printf("%s%d", (info.ac_state == 0 && state == TRUE) ? "-" : "", info.battery_life);

	return 0;
}
