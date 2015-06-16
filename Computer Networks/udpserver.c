#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#ifdef WIN
#include <winsock.h>
#include <windows.h>
#endif
#ifndef WIN
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif
#define PORT 20009
/* simple upd server 
   this program receives short messages (<99 characters) from any IP address
   and writes them to the display
   be sure to use the linker line option "-l wsock32"
*/
int main()
{
    /* first define a socket
    a socket is an I/O port like a file descriptor
    */
#ifdef WIN
      SOCKET sock;   /* SOCKET is a typedef for a structure */
#else
      int sock;
#endif
      int size;
      int nbytes, flags;
#ifdef WIN
      int addrlen;
#else
      socklen_t addrlen;
#endif
      int i;
      /* char loopback[20]="127.0.0.1"; */
#ifdef WIN
      WSADATA wsaData;              /* This is struct holds Windows required data */
      int nCode;
#endif
      char buffer[100];
      struct sockaddr_in server;    /* this holds my IP address and port info */
      struct sockaddr_in from;      /* this holds the same info for the sender of the packet
                                       I received */
      /* the call to WSAStartup is Windows magic */
#ifdef WIN
      if((nCode = WSAStartup(MAKEWORD(1,1), &wsaData)) != 0){
      printf("Opps! WSA error %d\n",nCode);
      exit;
      }
#endif
      /* create a socket called sock. It is a datagram socket */
      sock = socket(AF_INET,SOCK_DGRAM,0);
       if(sock < 0){
       printf("socket error = %d\n", sock);
       return -1;
       }
      server.sin_family = AF_INET;   /* initialize the server address family */
      server.sin_addr.s_addr = htonl(INADDR_ANY); /* notice this struct within a struct */
      /* printf("%x\n",server.sin_addr.s_addr); */
      server.sin_port = htons(PORT);
      /* associate the socket with the address structure - this is called binding */
      i = bind(sock, (struct sockaddr *) &server, sizeof(server));
      if( i < 0) {
          printf("bind result: %d\n", i);
          return -1;
          } else
          printf("Simple UDP server is ready!\n\n");
      nbytes = 99; /* receive packets up to 99 bytes long */
       flags = 0;  /* must be zero or this will not work! */
      while(1){
      /* the recvfrom function is a read and the arguments are:
             sock - the socket we are reading
             buffer - array into which to read the data
             nbytes - read up to this many bytes
             flags - used for special purposes - not needed here
             from - sockaddr struct to hold the IP address and port of the sender of the packet
             addrlen - the size of the sockaddr struct written by this function
      */
         addrlen = sizeof(from);
         size = recvfrom(sock, buffer, nbytes, flags, (struct sockaddr *)&from,&addrlen);
         if((size > 0) && (size < 99)){
         buffer[size] = '\0';      /* add the null byte so buffer now holds a string */
         i = puts((char *) buffer);    /* write this string to the display */
         }
      }
#ifdef WIN
      system("PAUSE");
#endif
      return 0;
}

