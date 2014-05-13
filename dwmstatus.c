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

#define GAP " \uE196 " /* see readme#icons */
#define DATESTR "%a %d %b \uE015 %H:%M" /* see strftime, and readme#icons */
#define TASKFILE "/home/luk/.TASK"

  static Display *dpy;
  void setstatus(char *str);

int
main(void)
{
    time_t tim;

    char status[100];
    char buf[30];
	FILE *infile;

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "dwmstatus: cannot open display.\n");
        return 1;
    }

    for (;;sleep(SLEEP)) {

        /* see man strcat */
        status[0] = '\0';

        /* task !reads only till whitespace! */
		infile = fopen(TASKFILE,"r");
		fscanf(infile,"%s", buf);fclose(infile);
        strcat(status, buf);
        strcat(status, GAP);


        /* date & time */
        tim = time(NULL);
        if (!strftime(buf, sizeof(buf)-1, DATESTR, localtime(&tim))) {
            fprintf(stderr, "strftime == 0\n");
            exit(1);
        }		
        strcat(status, buf);

        /* output */
        setstatus(status);
    }

    /* should never execute */
    XCloseDisplay(dpy);

    return 0;
}

  void
  setstatus(char *str)
  {
      XStoreName(dpy, DefaultRootWindow(dpy), str);
      XSync(dpy, False);
  }
