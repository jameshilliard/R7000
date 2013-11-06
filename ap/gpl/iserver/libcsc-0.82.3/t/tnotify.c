#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	"libcsc.h"


static CSCnotificationBoardType   m_board = NULL;

static int          TagFlag11 = 52;
static CSCboolean   RunFlag11 = CSC_TRUE;
static int          TagFlag12 = 51;
static CSCboolean   RunFlag12 = CSC_TRUE;

static CSCboolean   RunFlag21 = CSC_TRUE;
static int          TagFlag21 = 3;
static CSCboolean   RunFlag22 = CSC_TRUE;
static int          TagFlag22 = 2;
static CSCboolean   RunFlag23 = CSC_TRUE;
static int          TagFlag23 = 1;


static int   eventOneErrFn (
                           int     flagZ,
                           int     notificationCount,
                           void*   notificationName
                           )
   {
   printf ("\n");
   printf ("Error function for EVENT_ONE called:\n");
   printf ("\t            flagZ:  %d\n", flagZ);
   printf ("\tnotificationCount:  %d\n", notificationCount);
   printf ("\t notificationName:  %s\n", (char*)notificationName);
   printf ("\n");
   }


static int   eventTwoErrFn (
                           int     flagZ,
                           int     notificationCount,
                           void*   notificationName
                           )
   {
   printf ("\n");
   printf ("Error function for EVENT_TWO called:\n");
   printf ("\t            flagZ:  %d\n", flagZ);
   printf ("\tnotificationCount:  %d\n", notificationCount);
   printf ("\t notificationName:  %s\n", (char*)notificationName);
   printf ("\n");
   }


static int   eventOneFn (
                        int     notificationCount,
                        int     myTag,
                        void*   myData
                        )
   {
   printf ("\n");
   printf ("EVENT_ONE handler called:\n");
   printf ("\tnotificationCount:  %d\n", notificationCount);
   printf ("\t            myTag:  %d\n", myTag);
   printf ("\t           myData:  %s\n", (char*)myData);
   printf ("\n");
   return (CSC_NOTFOUND);
   }


static int   eventTwoFn (
                        int     notificationCount,
                        int     myTag,
                        void*   myData
                        )
   {
   printf ("\n");
   printf ("EVENT_TWO handler called:\n");
   printf ("\tnotificationCount:  %d\n", notificationCount);
   printf ("\t            myTag:  %d\n", myTag);
   printf ("\t           myData:  %s\n", (char*)myData);
   printf ("\n");
   return (CSC_NOTFOUND);
   }


static const char*   const monData = "this is monitor data";

static int   monitor (
                     CSCioSwitchType   ioSwitch,
                     void*             monData
                     )
   {
   (void)printf ("monitor [%s]", (char*)monData);
   switch (ioSwitch)
      {
      default:             (void)printf (" UNKNOWN ");  break;
      case CSC_IO_INPUT:   (void)printf (" IN ");       break;
      case CSC_IO_OUTPUT:  (void)printf (" OUT ");      break;
      case CSC_IO_NULL:    (void)printf (" NULL ");     break;
      }
   (void)printf ("\n");
   return (CSC_OK);
   }


int   main (void)
   {
   int   stat;

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("Create a notification board.\n");

   printf ("\n");
   printf ("1)\tCreating a new notification board.\n");
   printf ("  \tm_board = %p\n", m_board);
   printf ("  \tm_board = CSCnotificationBoardNew (\n");
   printf ("  \t                                  \"my board\",\n");
   printf ("  \t                                  monitor,\n");
   printf ("  \t                                  monData,\n");
   printf ("  \t                                  CSC_DO_PROFILING\n");
   printf ("  \t                                  );\n");
   m_board = CSCnotificationBoardNew ("my board", monitor, monData, CSC_DO_PROFILING);
   printf ("  \tm_board = %p\n", m_board);

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("2)\tCreate a notification EVENT_ONE.\n");
   printf ("  \tstat = CSCnotificationNew (\n");
   printf ("  \t                          m_board,\n");
   printf ("  \t                          \"EVENT_ONE\",\n");
   printf ("  \t                          eventOneErrFn\n");
   printf ("  \t                          );\n");
   stat = CSCnotificationNew (m_board, "EVENT_ONE", eventOneErrFn);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("3)\tCreate a notification EVENT_TWO.\n");
   printf ("  \tstat = CSCnotificationNew (\n");
   printf ("  \t                          m_board,\n");
   printf ("  \t                          \"EVENT_TWO\",\n");
   printf ("  \t                          eventTwoErrFn\n");
   printf ("  \t                          );\n");
   stat = CSCnotificationNew (m_board, "EVENT_TWO", eventTwoErrFn);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("4)\tDelete a notification EVENT_ONE.\n");
   printf ("  \tstat = CSCnotificationDel (m_board, \"EVENT_ONE\");\n");
   stat = CSCnotificationDel (m_board, "EVENT_ONE");
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("5)\tCreate a notification EVENT_ONE (again).\n");
   printf ("  \tstat = CSCnotificationNew (\n");
   printf ("  \t                          m_board,\n");
   printf ("  \t                          \"EVENT_ONE\",\n");
   printf ("  \t                          eventOneErrFn\n");
   printf ("  \t                          );\n");
   stat = CSCnotificationNew (m_board, "EVENT_ONE", eventOneErrFn);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("6)\tRegister a handler for EVENT_ONE.\n");
   printf ("  \tstat = CSCnotificationRegister (\n");
   printf ("  \t                               m_board,\n");
   printf ("  \t                               \"EVENT_ONE\",\n");
   printf ("  \t                               \"1st Handler\",\n");
   printf ("  \t                               eventOneFn,\n");
   printf ("  \t                               &RunFlag11,\n");
   printf ("  \t                               &TagFlag11,\n");
   printf ("  \t                               \"data for 1st handler EVENT_ONE\"\n");
   printf ("  \t                               );\n");
   stat = CSCnotificationRegister (
                                  m_board,
                                  "EVENT_ONE",
                                  "1st Handler",
                                  eventOneFn,
                                  &RunFlag11,
                                  TagFlag11,
                                  "data for 1st handler EVENT_ONE"
                                  );
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("7)\tRegister another handler for EVENT_ONE.\n");
   printf ("  \tstat = CSCnotificationRegister (\n");
   printf ("  \t                               m_board,\n");
   printf ("  \t                               \"EVENT_ONE\",\n");
   printf ("  \t                               \"2nd Handler\",\n");
   printf ("  \t                               eventOneFn,\n");
   printf ("  \t                               &RunFlag12,\n");
   printf ("  \t                               &TagFlag12,\n");
   printf ("  \t                               \"data for 2nd handler EVENT_ONE\"\n");
   printf ("  \t                               );\n");
   stat = CSCnotificationRegister (
                                  m_board,
                                  "EVENT_ONE",
                                  "2nd Handler",
                                  eventOneFn,
                                  &RunFlag12,
                                  TagFlag12,
                                  "data for 2nd handler EVENT_ONE"
                                  );
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("8)\tPost EVENT_ONE.\n");
   printf ("   \tstat = CSCnotificationPost (m_board, \"EVENT_ONE\");\n");
   stat = CSCnotificationPost (m_board, "EVENT_ONE");
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("9)\tPost EVENT_ONE with higher priority event run flag off.\n");
   RunFlag12 = CSC_FALSE;
   printf ("   \tstat = CSCnotificationPost (m_board, \"EVENT_ONE\");\n");
   stat = CSCnotificationPost (m_board, "EVENT_ONE");
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("10)\tRegister 1st handler for EVENT_TWO.\n");
   printf ("  \tstat = CSCnotificationRegister (\n");
   printf ("  \t                               m_board,\n");
   printf ("  \t                               \"EVENT_TWO\",\n");
   printf ("  \t                               \"1st Handler\",\n");
   printf ("  \t                               eventTwoFn,\n");
   printf ("  \t                               &RunFlag21,\n");
   printf ("  \t                               &TagFlag21,\n");
   printf ("  \t                               \"data for 1st handler EVENT_TWO\"\n");
   printf ("  \t                               );\n");
   stat = CSCnotificationRegister (
                                  m_board,
                                  "EVENT_TWO",
                                  "1st Handler",
                                  eventTwoFn,
                                  &RunFlag21,
                                  TagFlag21,
                                  "data for 1st handler EVENT_TWO"
                                  );
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("11)\tRegistering 2nd handler for EVENT_TWO.\n");
   printf ("  \tstat = CSCnotificationRegister (\n");
   printf ("  \t                               m_board,\n");
   printf ("  \t                               \"EVENT_TWO\",\n");
   printf ("  \t                               \"2nd Handler\",\n");
   printf ("  \t                               eventTwoFn,\n");
   printf ("  \t                               &RunFlag22,\n");
   printf ("  \t                               &TagFlag22,\n");
   printf ("  \t                               \"data for 2nd handler EVENT_TWO\"\n");
   printf ("  \t                               );\n");
   stat = CSCnotificationRegister (
                                  m_board,
                                  "EVENT_TWO",
                                  "2nd Handler",
                                  eventTwoFn,
                                  &RunFlag22,
                                  TagFlag22,
                                  "data for 2nd handler EVENT_TWO"
                                  );
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("12)\tRegistering 3rd handler for EVENT_TWO.\n");
   printf ("  \tstat = CSCnotificationRegister (\n");
   printf ("  \t                               m_board,\n");
   printf ("  \t                               \"EVENT_TWO\",\n");
   printf ("  \t                               \"3rd Handler\",\n");
   printf ("  \t                               eventTwoFn,\n");
   printf ("  \t                               &RunFlag23,\n");
   printf ("  \t                               &TagFlag23,\n");
   printf ("  \t                               \"data for 3rd handler EVENT_TWO\"\n");
   printf ("  \t                               );\n");
   stat = CSCnotificationRegister (
                                  m_board,
                                  "EVENT_TWO",
                                  "3rd Handler",
                                  eventTwoFn,
                                  &RunFlag23,
                                  TagFlag23,
                                  "data for 3rd handler EVENT_TWO"
                                  );
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("13)\tPost EVENT_TWO with middle priority event run flag off.\n");
   RunFlag22 = CSC_FALSE;
   printf ("   \tstat = CSCnotificationPost (m_board, \"EVENT_TWO\");\n");
   stat = CSCnotificationPost (m_board, "EVENT_TWO");
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("98)\tPrint the notification board.\n");
   printf ("   \t(void)CSCnotificationBoardPrint (m_board);\n");
   (void)CSCnotificationBoardPrint (m_board);

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("99)\tDelete the notification board.\n");
   printf ("  \tboard = %p\n", m_board);
   printf ("  \tstat = CSCnotificationBoardDel (m_board);\n");
   stat = CSCnotificationBoardDel (m_board);
   printf ("  \tstat = %d [%s]\n", stat, CSCstatStr(stat));

   printf ("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

   printf ("\n");
   printf ("Program exit.\n");
   printf ("\n");
   exit (EXIT_SUCCESS);
   }
