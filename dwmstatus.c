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
#define BUFSIZE 30

#define GAP " \uE196 " /* This is an icon, if you want to change this see README.md. */
#define DATEFMT "%a %d %b \uE015 %H:%M" /* Format for strftime(). */
#define TASKFILE "/home/luk/.TASK"

  static Display *dpy;
  void setstatus(char *str);

int
main(void)
{
    time_t tim;

    char status[100];
    char buf[BUFSIZE];
    FILE *infile;

    if (!(dpy = XOpenDisplay(NULL))) {
        fprintf(stderr, "dwmstatus: cannot open display.\n");
        return 1;
    }

    for (;;sleep(SLEEP)) {

        /* initialize empty string */
        status[0] = '\0';
        buf[0] = '\0';

        /* task - strings only up to BUFSIZE */
        infile = fopen(TASKFILE,"r");
        for (int i = 0; i < BUFSIZE; i++) {
            buf[i] = fgetc(infile);
            if (buf[i] == '\n' || buf[i] == EOF) {
                buf[i] = '\0';
                break;
            }
        }
        fclose(infile);
        if (buf[0] != '\0') {
            strcat(status, buf);
            strcat(status, GAP);
        }


        /* date & time */
        tim = time(NULL);
        if (!strftime(buf, sizeof(buf)-1, DATEFMT, localtime(&tim))) {
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
