dwmstatus-1uk
=============
my personal fork of dwmstatus.

## Dependencies
I use [stlarch_font](http://sourceforge.net/projects/stlarchfont/ "sourceforge") for icons and [terminus-font](http://sourceforge.net/projects/terminus-font/ "sourceforge") for letters. Either you install them or amend dwmstatus.c.

## Features
### task
Reads the first line of the defined TASKFILE and prints it.
### current time
Just date and hour, minutes. No seconds - could be distracting.
### pretty icons (font in dwm's config.h)
To view or modify the icons convert the font to bdf format `pcf2bdf -o out.bdf in.pcf`, then open with [gbdfed](http://sofia.nmsu.edu/~mleisher/Software/gbdfed/).

## Todo
* battery if low
* volume
