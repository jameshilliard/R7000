/*
**    BPALogin - lightweight portable BIDS2 login client
**    Copyright (c) 2001-3 Shane Hyde, and others.
** 
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
** 
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
*/ 

/**
 * Changes:
 * 2001-09-19:  wdrose    Fixed incorrect use of single fork() to put
 *                        BPALogin into background.  Replaced with
 *                        fork(), setsid(), fork().
 *
 * 2001-12-05:  wdrose    Added fix gleaned from Sam Johnston to include
 *                        errno.h for errno, rather than assuming it is an
 *                        extern int.
 */
#include "bpalogin.h"

#define BPALOGIN_BANNER \
        "BPALogin v2.0.2 - portable BigPond Broadband login client"

struct session s;
int debug_level = DEFAULT_DEBUG;
int dosyslog = 1;

int parse_parms(struct session *,char * conffile);
void usage( void );
void debug(int l,char *s,...);

void onconnected(int i)
{
    if(strcmp(s.connectedprog,""))
    {
        char buf[500];
        sprintf(buf,"%.500s %d",s.connectedprog,s.listenport);

        debug(0,"Executing external command - %s\n",buf);
        system(buf);
    }
}

void ondisconnected(int reason)
{
    if(strcmp(s.disconnectedprog,"killall bpalogin"))
    {
        char buf[500];
        sprintf(buf,"%.500s %d",s.disconnectedprog,reason);

        debug(0,"Executing external command - %s\n",buf);
        system(buf);
    }
}

#if 0
int onstatechange(FILE *fp, int state)
{
				fprintf(fp,"%s",state);
				fclose(fp);
				printf("state=%s\r\n",state);
}
#endif

void critical(char *s)
{
#if defined(USE_SYSLOG) /* foxconn wklin added, 08/13/2007 */
    if(dosyslog)
    syslog(LOG_CRIT,"Critical error: %s\n",s);
    else
#endif
    printf("Critical error: %s\n",s);
    exit(1);
}

void debug(int l,char *s,...)
{
    va_list ap;
    va_start(ap,s);
    if(debug_level > l)
    {
        int pri;
        char buf[256];

        switch(l)
        {
        case 0:
            pri = LOG_INFO;
            break;
        case 1:
            pri = LOG_INFO;
            break;
        case 2:
        case 3:
        default:
            pri = LOG_INFO;
            break;
        }
        vsprintf(buf,s,ap);
#if defined(USE_SYSLOG) /* foxconn wklin added, 08/13/2007 */
        if(dosyslog)
        syslog(pri,"%s",buf);
        else
#endif
        printf("%s",buf);
    }
    va_end(ap);
}

void noncritical(char *s,...)
{
    char buf[256];

    va_list ap;
    va_start(ap,s);
    vsprintf(buf,s,ap);
#if defined(USE_SYSLOG) /* foxconn wklin added, 08/13/2007 */
    if(dosyslog)
    syslog(LOG_CRIT,buf);
    else
#endif
    printf(buf);
    va_end(ap);
}

void onsignal(int i)
{
    logout(0,&s);

    /* Foxconn added start by EricHuang, 09/29/2007 */
#ifndef U12H092
    s.ondisconnected(0);
#endif
    /* Foxconn added end by EricHuang, 09/29/2007 */

    /* Foxconn added start, zacker, 07/09/2008,
     * sometimes it can't logout seccessful */
    s.state = STATE_IDLE_LOGOFF;
    bpa_state(s.state);
    /* Foxconn added end, zacker, 07/09/2008 */

    closelog();
    exit(1);
}

/* Foxconn added start, Jared Hsu, 03/15/2006 */
void bpa_state(int state)
{
    FILE *pidfile;
    
    if ((pidfile = fopen("/tmp/bpa.conf", "w")) != NULL) 
    {
				fprintf(pidfile, "%d\n", state);
				(void) fclose(pidfile);
    } 
    else 
    {
				error("Failed to create pid file\r\n");
    }
}
/* Foxconn added end, Jared Hsu, 03/15/2006 */

int main(int argc,char* argv[])
{
    int makedaemon = 1;
    char conffile[256];

    int c;

    int sock;
    struct ifreq ifr;


    /*
    ** Signal handler and Utility Func register 
    */ 		 
    signal(SIGINT,onsignal);
    signal(SIGHUP,onsignal);
    signal(SIGTERM,onsignal);
    signal(SIGALRM,onsignal);

    s.debug = debug;
    s.critical = critical;
    s.noncritical = noncritical;
    s.onconnected = onconnected;


    /*
    **	initiate value to the default 
    **  some value will be override when parameters are parsed
    */
    strcpy(s.authserver,DEFAULT_AUTHSERVER);
    strcpy(s.authdomain,DEFAULT_AUTHDOMAIN);
    s.authport = DEFAULT_AUTHPORT;
    strcpy(s.username,"");
    strcpy(s.password,"");
    /*
    **  Foxconn add : Steve Hsieh : 2005-10-21 : bpaclient porting
    */
		
    strcpy(s.password_hashed,"");
    
    strcpy(s.connectedprog,"");
    strcpy(s.disconnectedprog,"");
    strcpy(s.localaddress,"");
    s.localport = 0;
    s.minheartbeat = 60;
    s.maxheartbeat = 420;
    /* Foxconn added start, Jared Hsu, 03/15/2006 */
    s.state = STATE_NEED_PROTOCOL;
    bpa_state(s.state);
		/* Foxconn added end, Jared Hsu, 03/15/2006 */
		
    /*
    ** Parse the arg passed in to set log method  and dbg level
    */
	
    optind = 1;
/* Foxconn modified start, Jared Hsu, 2006/02/23 */
    while( (c = getopt( argc, argv, "u:p:s:c:d:l:D" )) > -1 ) 
    {
        switch( c ) 
        {
        case 'u':
              strcpy(s.username, optarg);
        			break;
        case 'p':	
            	strcpy(s.password, optarg);
            	break;
        case 's':	
            	strcpy(s.authserver, optarg);
            	break;
/* Foxconn modified end, Jared Hsu, 2006/02/23 */
        case 'D':
            makedaemon = 0;
            break;
        case 'c':
            break;
        case 'd':
            debug_level = atoi(optarg);
            break;
	case 'l':
	    if( strcasecmp( optarg, "stdout" ) == 0 )
	      	dosyslog = 0;
	    else
		dosyslog = 1;
	    break;
        case '?':
            usage();
            exit(1);
            break;
        case ':':
            break;
        }
    }

    if(makedaemon) {
      /**
       * Original code did not perform the setsid() or second fork(), and
       * hence did not correctly make itself a daemon.  There is a library
       * call in FreeBSD (daemon) that does the actions below, but the
       * portability is unknown.
       */
      switch( fork() ) {
        case 0:
          break;
          
        case -1:
          perror("Could not run BPALogin in the background");
          exit(1);
          break;
          
        default:
          exit(0);
          break;
      }

      if( setsid() < 0 ) {
        perror("Could not run BPALogin in the background");
        exit(1);
      }

      /**
       * while not strictly necessary, the second fork ensures we stay
       * detached from a terminal by preventing the program using its
       * status as session leader to regain a terminal.
       */
      switch( fork() ) {
        case 0:
          break;

        case -1:
          perror("Could not run BPALogin in the background");
          exit(1);
          break;

        default:
          exit(0);
          break;
      }
    }
    

    openlog("bpalogin",LOG_PID,LOG_DAEMON);

#if defined(USE_SYSLOG) /* foxconn wklin added, 08/13/2007 */
    if(dosyslog)    
        syslog( LOG_INFO, BPALOGIN_BANNER "\n" );
    else
#endif
        printf( BPALOGIN_BANNER "\n");


#if 0 //move into the mainloop so that the relogin can check para and ip first
    /*
    ** Parsing parameter from nvram 
    */	
    if(!parse_parms(&s,conffile)) {
        printf("[ bpaclient ] : parameter read error" );
        //usage();
        exit(1);
    }
    s.debug(0,"parameter parsing:\n");	
    printf("username = %s\n",s.username);	
    printf("password = %s\n",s.password);
    printf("server   = %s\n",s.authserver);
    printf("minHB    = %d\n",s.minheartbeat);
    printf("maxHB    = %d\n",s.maxheartbeat);
    printf("localport= %d\n",s.localport);



    if(!strcmp(s.username,""))
    {
        critical("Username has not been set");
        exit(1);
    }
    if(!strcmp(s.password,""))
    {
        critical("Password has not been set");
        exit(1);
    }


    /*
    **  sleep until wanside get IP
    */
    if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0)
    	printf("[ bpaclient ]: sock open error\n");
	
    memset(&ifr,0,sizeof(struct ifreq));
    strcpy(ifr.ifr_name,"eth0");		
    do
    {
	sleep(POLL_CYCLE);
	if (ioctl(sock,  SIOCGIFADDR, &ifr))
		s.debug(2,"ioctl error!!\n");
	
	s.debug(2,"ipaddress of eth0 : %s",inet_ntoa(((struct sockaddr_in*)(&ifr.ifr_addr))->sin_addr));
    }while(!strcmp(inet_ntoa(((struct sockaddr_in*)(&ifr.ifr_addr))->sin_addr),"0.0.0.0"));
    
    //closesocket(sock);
#endif
   
    while(mainloop(&s));
    
    s.ondisconnected(0);
		//s.state = STATE_IDLE_LOGOFF;
		//s.onstatechange(s.fp,"STATE_IDLE_LOGOFF");
		
    exit(0);
}

int parse_parms(struct session *s,char * conffile)
{
/* *** Foxconn Add Start : Steve Hsieh : 2005-10-17 (bpalogin porting) *** */
    
    /*
    ** 	read the param from nvram 
    */	
    
    char tmp[100], prefix[] = "wan_";
    char *buf = 0;
    
#if 0
    if(!(buf = nvram_get(strcat_r(prefix, "bpa_username", tmp))) )
    	return	FALSE;
    
    strcpy(s->username,buf);
#else
    /* strcpy(s->username, "bpa-user"); */ /* Foxconn removed, Jared Hsu, 2006/02/23 */ 
#endif
    
    debug(2,"parse username : %s\n",s->username);
    		
#if 0
    if((buf = nvram_get(strcat_r(prefix, "bpa_passwd", tmp))) == NULL ) 	
    	return FALSE;
    	 	
    strcpy(s->password,buf);
#else
    /* strcpy(s->password, "bpa-passwd"); */ /* Foxconn removed, Jared Hsu, 2006/02/23 */ 
#endif
    
    debug(2,"parse password : %s\n",s->password);		
   
#if 0  
    if(!(buf = nvram_get(strcat_r(prefix, "bpa_server", tmp))) ) 		
    	return FALSE;
	 	
    strcpy(s->authserver,buf);
#else
    /* strcpy(s->authserver, "1.2.3.4"); */ /* Foxconn removed, Jared Hsu, 2006/02/23 */ 
#endif
    debug(2,"parse server : %s\n",s->authserver);
    		
#if 0
    if(!(buf = nvram_get(strcat_r(prefix, "bpa_minheartbeat", tmp))) ) 		
    	return FALSE;	 	
    
    s->minheartbeat = atoi(buf);
#else
    s->minheartbeat = 2;
#endif
    debug(2,"parse minheartbeat : %d\n",s->minheartbeat);
    		
#if 0
    if(!(buf = nvram_get(strcat_r(prefix, "bpa_maxheartbeat", tmp))) ) 		
    	return FALSE;
	 	
    s->maxheartbeat = atoi(buf);
#else
    s->maxheartbeat = 600;
#endif
    debug(2,"parse maxheartbeat : %d\n",s->maxheartbeat);
    		
		
#if 0
    if(!(buf = nvram_get(strcat_r(prefix, "bpa_localport", tmp))) ) 		
    	return FALSE;
	 	
    s->localport = atoi(buf);
#else
    s->localport = 5050;
#endif
    debug(2,"parse local port : %d\n",s->localport);
    
	
    return TRUE;
}

void usage( void )
{
    printf( BPALOGIN_BANNER "\n");
    printf("Copyright (c) 2001-3 Shane Hyde and others\n\n");
    printf("This program is *not* a product of Big Pond Advance\n\n");
    printf("Usage: bpalogin [-c file] [-d level] [-l style] [-D]\n\n");
/* Foxconn added start, Jared Hsu, 2005/02/23 */
    printf(" -u username        Username\n");
    printf(" -p password        Password\n");
    printf(" -s server		Server\n");
/* Foxconn added end, Jared Hsu, 2005/02/23 */
    printf(" -d level           Set the verbosity of log messages\n");
    printf("                    (0 is quiet, 2 is most verbose)\n\n");
    printf(" -l style           Use syslog or stdout for messages\n\n" );
    printf(" -D                 Dont run bpalogin as a daemon (run in "
           "foreground)\n\n");
}

int closesocket(int s)
{
    return close(s);
}

void socketerror(struct session *s, const char * str)
{
    char buf[200];
    sprintf(buf,"%.100s - %.80s",str,strerror(errno));
    s->noncritical(buf);
}
