#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>


int main()
{
  Display *ourDisplay;
  Window myWindow, rootWindow;
  int ourScreen;
  unsigned long bgcolor;
  
  ourDisplay = XOpenDisplay(NULL);
  if (ourDisplay == NULL)
    {
      printf ("Failed to connect to graphical terminal.\n");
      return 1;
    }
/*получаем предварительные сведения*/  
  ourScreen = DefaultScreen(ourDisplay);           //экран по умолчанию
  rootWindow = RootWindow(ourDisplay, ourScreen);  //корневое окно
  bgcolor = WhitePixel (ourDisplay, ourScreen);    //белый цвет экрана

  /*открываем окно*/
  myWindow = XCreateSimpleWindow(ourDisplay,rootWindow,100,100,320,200,0,0,bgcolor);

  /*делаем окно видимым*/
  XMapWindow(ourDisplay, myWindow);

  /*все сформированные команды принудительно сбрасываем на сервер*/
  XFlush(ourDisplay);

 
  sleep(5);

  /*уничтожаем окно*/
  XDestroyWindow(ourDisplay, myWindow);

  /*закрываем соединение с сервером*/
  XCloseDisplay(ourDisplay);

  return 0;
}
