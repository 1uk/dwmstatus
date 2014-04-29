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
#define DATESTR "%a %d %b"      /* weekday, daynumber, monthnumber (see strftime manpage) */

  char *tzberlin = "Europe/Berlin";

  static Display *dpy;

  void
  setstatus(char *str)
  {
      XStoreName(dpy, DefaultRootWindow(dpy), str);
      XSync(dpy, False);
  }


int
main(void)
{
    time_t tim;

    char status[100];
    char buf[100];

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "dwmstatus: cannot open display.\n");
        return 1;
    }

    for (;;sleep(SLEEP)) {

        /* date & time */
        tim = time(NULL);
        if (!strftime(buf, sizeof(buf)-1, CLOCKSTR, localtime(&tim))) {
            fprintf(stderr, "strftime == 0\n");
            exit(1);
        }
        
        
        sprintf(status, "%s",
                buf);
        setstatus(status);
        free(buf);
        free(status);
    }

    /* should never execute */
    XCloseDisplay(dpy);

    return 0;
}
