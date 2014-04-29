#define _BSD_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <strings.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <X11/Xlib.h>

#define SLEEP 55

#define CLOCKSTR "\uE015 %H:%M" /* icon, hour, minute */
#define DATESTR "%a %d %b| "      /* weekday, daynumber, monthnumber (see strftime manpage) */

char *tzberlin = "Europe/Berlin";

static Display *dpy;

char *
mktimes(char *fmt, char *tzname)
{
	char buf[129];
	time_t tim;
	struct tm *timtm;

	memset(buf, 0, sizeof(buf));
    setenv("TZ", tzname, 1);
	tim = time(NULL);
	timtm = localtime(&tim);
	if (timtm == NULL) {
		perror("localtime");
		exit(1);
	}

	if (!strftime(buf, sizeof(buf)-1, fmt, timtm)) {
		fprintf(stderr, "strftime == 0\n");
		exit(1);
	}

	return smprintf("%s", buf);
}

void
setstatus(char *str)
{
	XStoreName(dpy, DefaultRootWindow(dpy), str);
	XSync(dpy, False);
}


int
main(void)
{
	char *status;
	char *statnext;
	char *ckbln;
    char *dtbln;

	if (!(dpy = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}

	for (;;sleep(SLEEP)) {
		ckbln = mktimes(CLOCKSTR, tzberlin);
		dtbln = mktimes(DATESTR, tzberlin);

		sprintf(*status, "%s %s",
				dtbln, ckbln);
		setstatus(status);
		free(ckbln);
		free(status);
	}

	XCloseDisplay(dpy);

	return 0;
}

