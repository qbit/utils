/*	$OpenBSD$	*/

/*
 * Copyright (c) 2018 Aaron Bieber <aaron@bolddaemon.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/ioctl.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <fcntl.h>

#include <machine/apmvar.h>

#define FALSE 0
#define TRUE 1

__dead void	usage(void);

__dead void
usage(void)
{
	extern char	*__progname;
	fprintf(stderr, "usage: battery [-ahnp]\n");
	exit(1);
}

int
main(int argc, char **argv)
{
	int apmfd, ch;
	int cr = TRUE;
	int state = FALSE;
	int percent = FALSE;
	struct apm_power_info info;
	while ((ch = getopt(argc, argv, "ahnp")) != -1) {
		switch(ch) {
		case 'a':
			state = TRUE;
			break;
		case 'h':
			usage();
		case 'n':
			cr = FALSE;
			break;
		case 'p':
			percent = TRUE;
			break;
		default:
			usage();
		}
	}

	apmfd = open("/dev/apm", O_RDONLY);
	ioctl(apmfd, APM_IOC_GETPOWER, &info);

	if (pledge("stdio rpath wpath cpath", NULL) == -1)
		err(1, "pledge");

	if (info.battery_state != APM_BATTERY_ABSENT) {
		if (cr)
			printf("%s%d%s\n", (info.ac_state == 0 && state == TRUE) ? "-" : "",
					info.battery_life,
					(percent == TRUE) ? "%" : "");
		else
			printf("%s%d%s", (info.ac_state == 0 && state == TRUE) ? "-" : "",
					info.battery_life,
					(percent == TRUE)? "%" : "");
	}

	return 0;
}

