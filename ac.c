#include <err.h>
#include <fcntl.h>
#include <machine/apmvar.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	int apmfd;
	struct apm_power_info info;

	apmfd = open("/dev/apm", O_RDONLY);
	ioctl(apmfd, APM_IOC_GETPOWER, &info);

	if (pledge("stdio rpath wpath cpath", NULL) == -1)
		err(1, "pledge");

	return info.ac_state == 0 ? 1 : 0;
}
