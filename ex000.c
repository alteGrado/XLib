#include <stdio.h>
#include <X11/Xlib.h>
int main()
{
  Display *ourDisplay;

  ourDisplay = XOpenDisplay(NULL);
  if (ourDisplay == NULL)
    {
      printf("Failed to connect to graphical terminal.\n");
      return 1;
    }
  printf ("Connected to the graphical terminal.\n");
  printf ("Connection number: %d\n",ConnectionNumber(ourDisplay));
  printf ("Version protocol is used %d.%d\n",
           ProtocolVersion(ourDisplay),ProtocolRevision(ourDisplay));
  printf ("Server developer: %s\n",ServerVendor(ourDisplay));
  printf ("Server version: %d\n", VendorRelease(ourDisplay));
  printf ("Connection string: [%s]\n",DisplayString(ourDisplay));  
  printf ("Number of screens on the server: %d\n", ScreenCount(ourDisplay));
  printf ("Default screen number: %d\n", DefaultScreen(ourDisplay));

  XCloseDisplay(ourDisplay);
  return 0;
}
