#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>

int main()
{
  int tty_fd = open("/dev/ttyO1",O_RDWR | O_NOCTTY);
  
  if (tty_fd < 0)
  {
      printf("Can't find or open device /dev/ttyS1");
      exit(-1);
  }
  
  struct termios ttys1_termios;
  
 if (tcgetattr(tty_fd,&ttys1_termios)!= 0)
 {
	printf("Error getting attr ");
	exit(-1);
 } 


  
  //INPUT FLAGS
  //IGNPAR 	- ingore bytes with parity errors
  //ICRNL  	- map CR to NL
    ttys1_termios.c_iflag = 0;//IGNPAR | ICRNL;
    
  // OUTPUT FLAGS   
    //OCRNL 	- map CR to NL on output
    //ttys1_termios.c_oflag = OCRNL;
    
    //CONTROL FLAGS
    //CS8 	- 8n1 8 bit, no parity, 1 stop bit
    //CLOCAL 	- ingore modem status lines
    //CREAD  	- enable receiving characaters

    //cfsetispeed(&ttys1_termios,B56000);
    //cfsetospeed(&ttys1_termios,B57600);
    ttys1_termios.c_cflag =  B57600 | CS8 | CLOCAL | CREAD;
    
    //LOCAL FLAGS
    //ICANON 	- canonical mode
    ttys1_termios.c_lflag = 0;//ICANON;
    
    //CONTROL CHARACTERS
    //ttys1_termios.c_cc[VMIN] = 250;
    
    //tcflush(tty_fd,TCIOFLUSH);
    tcsetattr(tty_fd,TCSANOW,&ttys1_termios);
    
    char receive_buffer[250];
    
    while (1)
    {
	int received  = read(tty_fd,receive_buffer,250);
	if (received > 0)
	{
		int ii;
		for (ii = 0; ii < received; ii++)
		{
			putc(receive_buffer[ii],stdout);
		}

	}
    }
    
    close(tty_fd);
    
  
}
