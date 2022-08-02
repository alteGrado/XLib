#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define X 0
#define Y 0
#define WIDTH 250
#define HEIGHT 200
#define WIDTH_MIN 150
#define HEIGHT_MIN 100
#define BORDER_WIDTH 5
#define TITLE "Press button!"
#define ICON_TITLE "Press button!"
#define PRG_CLASS "Press button!"

static void SetWindowManagerHints    (
    Display* display,
    char*    PClass,
    char*    argv[],
    int      argc,
    Window   window,
    int      x,
    int      y,
    int      win_wdt,
    int      win_hgt,
    int      win_wdt_min,
    int      win_hgt_min,
    char*    ptrTitle,
    char*    ptrITitle,
    Pixmap   pixmap    )
{
    XSizeHints size_hints;

    XWMHints wm_hints;
    XClassHint class_hint;
    XTextProperty windowname, iconname;

    if ( !XStringListToTextProperty (&ptrTitle, 1, &windowname) ||
         !XStringListToTextProperty (&ptrITitle, 1, &iconname ))
    {
	puts ("No memory!\n");
	exit (1);
    }

size_hints.flags = PPosition | PSize | PMinSize;
size_hints.min_width = win_wdt_min;
size_hints.min_height = win_hgt_min;
wm_hints.flags = StateHint | IconPixmapHint | InputHint;
wm_hints.initial_state = NormalState;
wm_hints.input = True;
wm_hints.icon_pixmap = pixmap;

class_hint.res_name = argv[0];
class_hint.res_class = PClass;

XSetWMProperties (display, window, &windowname, &iconname,argv,argc,
                  &size_hints, &wm_hints, &class_hint);
}
int main (int argc, char* argv[])
{
    Display* display;
    int screen_number;
    GC gc;
    XEvent report;
    Window window;

    if (( display = XOpenDisplay (NULL)) == NULL )
    {
	puts ("Can not connect to the X server!\n");
	exit (1);
    }

    screen_number = DefaultScreen (display);

    window = XCreateSimpleWindow ( display, RootWindow (display, screen_number), X, Y,
                                   WIDTH,HEIGHT,BORDER_WIDTH,BlackPixel (display,
                                    screen_number), WhitePixel (display, screen_number));
    SetWindowManagerHints        ( display, PRG_CLASS, argv, argc, window, X, Y, WIDTH,
                                   HEIGHT, WIDTH_MIN, HEIGHT_MIN, TITLE, ICON_TITLE, 0 );

    XSelectInput                 ( display, window, ExposureMask | ButtonPressMask
                                   | ButtonReleaseMask | KeyPressMask );

    XMapWindow                   ( display, window);

    while ( 1 )
    {
	XNextEvent (display, &report);
	gc = XCreateGC (display, window, 0, NULL);
        XSetForeground (display, gc, BlackPixel (display, 0));

        switch ( report.type)
        {
	    case Expose:
		if ( report.xexpose.count != 0)
		    break;

		XDrawString (display, window, gc, 25, 50, "Press button or any key to exit!",
                             strlen ("Press button or any key to exit!"));
		    break;

	    case ButtonPress:
		XClearWindow (display, window);
		XSetWindowBackground (display, window, rand());
		XDrawString (display, window, gc, 50, 50, "Press!", strlen ("Press!"));
                    break;

	    case ButtonRelease:
		XClearWindow (display,window);
		XSetWindowBackground (display,window, rand());
		XDrawString (display, window, gc, 50, 50, "Release!", strlen ("Release!"));
		    break;

	    case KeyPress:
		XCloseDisplay (display);
		exit (0);
	}
    XFreeGC (display, gc);
    }
return 0;
}






























