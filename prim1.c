#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define X 0
#define Y 0
#define WIDTH 200
#define HEIGHT 200
#define WIDTH_MIN 50
#define HEIGHT_MIN 50
#define BORDER_WIDTH 5
#define TITLE "Example"
#define ICON_TITLE "Example"
#define PRG_CLASS "Example"

/* SetWindowManagerHints - функция,которая передает информацию о свойствах
программы менеджеру окон. */

static void SetWindowManagerHints (
    Display* display,/*указатель на структуру Display*/
    char* PClass,    /*класс программы*/
    char* argv[],    /*аргументы программы*/
    int argc,        /*число аргументов*/
    Window window,   /*идентификатор окна*/
    int x,           /*координаты левого верхнего*/
    int y,           /*угла окна*/
    int win_wdt,     /*ширина окна*/
    int win_hgt,     /*высота окна*/
    int win_wdt_min, /*минимальная ширина окна*/
    int win_hgt_min, /*минимальная высота окна*/
    char* ptrTitle,  /*заголовок окна*/
    char* ptrITitle, /*заголовок пиктограммы окна*/
    Pixmap pixmap    /*рисунок пиктограммы*/
)
{
    XSizeHints size_hints; /*рекомендации о размерах окна*/

    XWMHints wm_hints;
    XClassHint class_hint;
    XTextProperty windowname, iconname;

    if (!XStringListToTextProperty (&ptrTitle, 1, &windowname) || !XStringListToTextProperty (&ptrTitle, 1, &iconname)) 
        {
	    puts ("No memory!\n");
	    exit (1);
        }
 
    size_hints.flags = PPosition | PSize | PMinSize; /*подсказки по размеру*/
    size_hints.min_width = win_wdt_min;
    size_hints.min_height = win_hgt_min;
    wm_hints.flags = StateHint | IconPixmapHint | InputHint;
    wm_hints.initial_state = NormalState;
    wm_hints.input = True;
    wm_hints.icon_pixmap = pixmap;
    class_hint.res_name = argv[0];
    class_hint.res_class = PClass;

    XSetWMProperties (display,window,&windowname,&iconname,argv,argc,&size_hints,&wm_hints,&class_hint);

}

int  main(int argc, char *argv[])
{
    Display* display;        /*Указатель на структуру Display*/
    int ScreenNumber;        /*Номер экрана*/
    GC gc;                   /*Графический контекст*/
    XEvent report;            /*Отчет о событии*/
    Window window;

/*Устанавливаем связь с сервером*/

if ((display = XOpenDisplay (NULL)) == NULL )
{
    puts ("Can not connect to the X Server!\n");
    exit (1);
}

/*Получаем номер основного экрана*/

ScreenNumber = DefaultScreen (display);

/*Создаем окно*/

window = XCreateSimpleWindow (display,RootWindow (display,ScreenNumber), X, Y, WIDTH, HEIGHT,
                              BORDER_WIDTH,BlackPixel(display,ScreenNumber),
                              WhitePixel (display, ScreenNumber) );

/*Задаем рекомендации для менеджера окон*/
SetWindowManagerHints (display, PRG_CLASS, argv, argc, window, X, Y, WIDTH, HEIGHT,
                       WIDTH_MIN, HEIGHT_MIN, TITLE, ICON_TITLE, 0 );

/*Выбираем события, которые будет обрабатывать программа*/

XSelectInput (display, window, ExposureMask | KeyPressMask);

/*Покажем окно*/
XMapWindow (display, window);

/*создадим цикл получения и оработки ошибок*/
while (1)
{
    XNextEvent (display, &report);

    switch (report.type)
    {
	case Expose :
	    /*запрос на перерисовку*/
	    if (report.xexpose.count !=0)
	        break;
	    gc = XCreateGC (display, window, 0, NULL);

            XSetForeground (display, gc, BlackPixel (display, 0));
            XDrawString ( display, window, gc, 20, 50,"First example", 
                          strlen ("First example"));
            XFreeGC (display, gc);
            XFlush (display);
            break;

        case KeyPress:
        /*Выход нажатием клавиши клавиатуры*/
            XCloseDisplay (display);
            exit (0);
      }
}
}


































































