    #include <stdio.h>   /* Standard input/output definitions */
    #include <string.h>  /* String function definitions */
    #include <unistd.h>  /* UNIX standard function definitions */
    #include <fcntl.h>   /* File control definitions */
    #include <errno.h>   /* Error number definitions */
    #include <termios.h> /* POSIX terminal control definitions */

    /*
     * 'open_port()' - Open serial port 1.
     *
     * Returns the file descriptor on success or -1 on error.
     */

    int
    open_port(void)
    {
      int fd; /* File descriptor for the port */


      fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
      if (fd == -1)
      {
       /*
	* Could not open the port.
	*/

	perror("open_port: Unable to open /dev/ttyUSB0 - ");
      }
      else
	fcntl(fd, F_SETFL, 0);

      return (fd);
    }

int main(void){
	int fd = open_port();
	struct termios options;
	tcgetattr(fd, &options);

	// Set BAUD (input and output)
	cfsetispeed(&options, B19200); // set baud to 19200
	cfsetospeed(&options, B19200);

	// Control flag options
  	options.c_cflag &= ~CSIZE; /* Mask the character size bits */
    	options.c_cflag |= CS8;    /* Select 8 data bits */

	options.c_cflag |= PARENB; /* Set Even Parity */
	options.c_cflag &= ~PARODD;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS7;

	options.c_lflag&= ~(ICANON | ECHO | ECHOE | ISIG); /* Raw input */

	tcsetattr(fd, TCSANOW, &options);
	int rd;
	char *buff;

	// RCV TEST
	fcntl(fd, F_SETFL, FNDELAY);
	rd=read(fd, buff, 100);
	printf("Bytes received are %d\n",rd);
	printf("%s",buff);

	// SEND TEST

	close(fd);
	return 1;
}
