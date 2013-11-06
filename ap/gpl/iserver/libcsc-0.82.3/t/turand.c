/* ************************************************************************* */
/*                                                                           */
/*      Included Files                                                       */
/*                                                                           */
/* ************************************************************************* */

#include	<fcntl.h>
#include	<math.h>
#include	<stdio.h>
#include	<unistd.h>
#include	"libcsc.h"


/* ************************************************************************* */
/*                                                                           */
/*      Executable Code - MAIN                                               */
/*                                                                           */
/* ************************************************************************* */

int   main (void)
   {
   int      ab;
   int      ac;
   double   px;
   double   py;
   int      i;
   int      j;
   int      y;
   double   d;

   for (j=0 ; j<5 ; j++)
      {

      if (access("/dev/random",R_OK) == 0)
         {
         int fd = open ("/dev/random", O_RDONLY);
         (void)read (fd, &y, 4);
         (void)close (fd);
         }
      else
         {
         y = 0xAAAAAAAA;
         }

      ab = 0;
      ac = 0;

      for (i=0 ; i<4000000 ; i++)
         {
         y = CSCurand (y, &d); px = d;
         y = CSCurand (y, &d); py = d;
         if (((px*px)+(py*py)) > 1.0)
            ab += 1;
         else
            ac += 1;
         }

      printf ("pi = %8.6f\n", ((float)4.0*(float)ac/((float)ab+(float)ac)));

      }

   exit (0);
   }

/* End of file. */
