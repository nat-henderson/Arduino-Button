#include <stdlib.h>
#define _WIN32_WINNT 0x0500
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include "rs232.h"
#include "serialproject.h"

int main()
{
  int i, n,
      cport_nr=2,        /* /dev/ttyS2 (COM3 on windows) */
      bdrate=9600;       /* 9600 baud */

  char buf[4096];
  HWND hWnd = GetConsoleWindow();
  ShowWindow(hWnd, SW_HIDE);


  if(OpenComport(cport_nr, bdrate))
  {
    printf("Can not open comport\n");
    return(0);
  }

  while(1)
  {
  n = PollComport(cport_nr, (unsigned char*)buf, 4095);
    if(n > 0)
	{
		buf[n] = 0;   /* always put a "null" at the end of a string! */
		int i = 0;
		if (strncmp(buf, "Input Received", 5) == 0)
		{
			do_stuff();
		}
	}
    Sleep(100);  /* it's ugly to use a sleeptimer, in a real program, change the while-loop into a (interrupt) timerroutine */
  }

  return(0);
}