#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "primelib.h"
#include "restart.h"

int copy2files(int fromfd1, int tofd1, int fromfd2, int tofd2) {
   int bytesread;
   int maxfd;
   int num;
   fd_set readset;  
   int totalbytes = 0;

   /* for prime */
   long long value = 0;
   int testbytes = 0;
   char buff[1024];


   if ((fromfd1 < 0) || (fromfd1 >= FD_SETSIZE) ||
       (tofd1 < 0) || (tofd1 >= FD_SETSIZE) ||
       (fromfd2 < 0) || (fromfd2 >= FD_SETSIZE) ||
       (tofd2 < 0) || (tofd2 >= FD_SETSIZE))
      return 0;
   maxfd = fromfd1;                     /* find the biggest fd for select */
   if (fromfd2 > maxfd)
      maxfd = fromfd2;
 
   for ( ; ; ) { 
      FD_ZERO(&readset);
      FD_SET(fromfd1, &readset);
      FD_SET(fromfd2, &readset);
      if (((num = select(maxfd+1, &readset, NULL, NULL, NULL)) == -1) &&
         (errno == EINTR)) 
         continue;
      if (num == -1) 
         return totalbytes;
      if (FD_ISSET(fromfd1, &readset)) {

         //testbytes = read(fromfd1,buff, 1024);

         //value = atoll(buff);       

         //if (isPrimeLongLong(value)){
         //   bytesread = write(tofd2, "1", 1);

            //break;
 
         //} else {
         //   bytesread = write(tofd2, "0", 1);
            //break;
         //}

         bytesread = readwrite(fromfd1, tofd1);
         if (bytesread <= 0)
            break;
         totalbytes += bytesread;
      }
      if (FD_ISSET(fromfd2, &readset)) {
         //bytesread = readwrite(fromfd2, tofd2);

         testbytes = read(fromfd2,buff, 1024);

         value = atoll(buff);       

         if (isPrimeLongLong(value)){
            bytesread = write(tofd1, "1", 1);
            bytesread = write(tofd1, "tc", 2);
            bytesread = write(tofd2, "1", 1);
            bytesread = write(tofd2, "ts", 2);
            break;
 
         } else {
            bytesread = write(tofd1, "0", 1);
            bytesread = write(tofd1, "tc", 2);
            bytesread = write(tofd2, "0", 1);
            bytesread = write(tofd2, "ts", 2);
            break;
         }

         
   
         if (bytesread <= 0) 
            break;
         totalbytes += bytesread;
      }
   }
   return totalbytes;
}
