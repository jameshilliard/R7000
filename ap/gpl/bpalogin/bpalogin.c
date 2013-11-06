/*
**	BPALogin - lightweight portable BIDS2 login client
**	Copyright (c) 2001-3 Shane Hyde, and others.
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

#include "bpalogin.h"
#include "bcmnvram.h"

/*
**  Main processing loop.  Logs in, handles heartbeats, and logs out on request
**
**  Returns - 0 - We are no longer connected, and should not retry.
**            1 - We are no longer connnected and should retry.
*/
int mainloop(struct session * s)
{
	int err;
	struct sockaddr_in listenaddr;
	struct hostent * he;
	int addrsize;

    int rawSock = 0;
    struct ifreq ifr;

	if(!parse_parms(s,NULL))
	{
    	s->debug(1,"[ bpaclient ] : parameter read error" );
        //usage();
        exit(1);
    }
    	
    s->debug(1,"parameter parsing:\n");
    s->debug(1,"username = %s\n",s->username);
    s->debug(1,"password = %s\n",s->password);
    s->debug(1,"server   = %s\n",s->authserver);
    s->debug(1,"minHB    = %d\n",s->minheartbeat);
    s->debug(1,"maxHB    = %d\n",s->maxheartbeat);
    s->debug(1,"localport= %d\n",s->localport);

    if(!strcmp(s->username,""))
    {
        critical("Username has not been set");
        exit(1);
    }
    
    if(!strcmp(s->password,""))
    {
        critical("Password has not been set");
        exit(1);
    }

    /*
     **  sleep until wanside get IP
     */
	if((rawSock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW))<0)
    	s->debug(1,"[ bpaclient ]: rawSock open error\n");
        	
    memset(&ifr,0,sizeof(struct ifreq));

    /* Foxconn modified start, zacker, 10/22/2008, @qos_v8 */
#if defined(U12H083)
    strcpy(ifr.ifr_name,"eth0.2");
#elif ( defined(U12H092) || defined(U12H155) )
    strcpy(ifr.ifr_name,"eth0");
#elif defined(U12H072) || defined(U12H114) || (defined U12H139) || defined(U12H127)
    strcpy(ifr.ifr_name, nvram_safe_get("wan_ifname"));
#else
    strcpy(ifr.ifr_name,"eth1");
#endif
    /* Foxconn modified end, zacker, 10/22/2008, @qos_v8 */

    do
    {
    	sleep(POLL_CYCLE);
        
        if (ioctl(rawSock,  SIOCGIFADDR, &ifr)<0)
        {
        	s->debug(2,"ioctl error!!\n");
            s->debug(2,"errno = %d\n",errno);
        }
        
        s->debug(2,"ipaddress of %s : %s\n",ifr.ifr_name,inet_ntoa(((struct sockaddr_in*)(&ifr.ifr_addr))->sin_addr));
    }
    while(!strcmp(inet_ntoa(((struct sockaddr_in*)(&ifr.ifr_addr))->sin_addr),"0.0.0.0"));

	close(rawSock);	

	s->lastheartbeat = 0;
	s->sequence = 0;
	s->listensock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	s->debug(2,"listen socket = %d \n",s->listensock);//steve add for dbg
	s->localaddr.sin_family = AF_INET;
	s->localaddr.sin_port = htons(s->localport);
	
	if(strcmp(s->localaddress,""))
	{
		s->debug(2,"Using local address %s\n",s->localaddress);
		he = gethostbyname(s->localaddress);

		if(he)
		{
			s->localaddr.sin_addr.s_addr = *((int*)(he->h_addr_list[0]));
		}
		else
		{
			s->localaddr.sin_addr.s_addr = inet_addr(s->localaddress);
		}
	}
	else
	{
		s->localaddr.sin_addr.s_addr = INADDR_ANY;
	}

	addrsize = sizeof(struct sockaddr_in);
	err = bind(s->listensock,(struct sockaddr *)&s->localaddr,sizeof(s->localaddr));
	err = getsockname(s->listensock,(struct sockaddr *)&listenaddr,&addrsize);

	s->sessionid = time(NULL);

	s->listenport = ntohs(listenaddr.sin_port);
	strcpy(s->osname,"whocares");
	strcpy(s->osrelease,"notme");

	he = gethostbyname(s->authserver);

	if(he)
	{
		s->authhost.sin_addr.s_addr = *((int*)(he->h_addr_list[0]));
	}
	else
	{
		s->authhost.sin_addr.s_addr = inet_addr(s->authserver);
	}
	
	s->authhost.sin_port = htons(s->authport);
	s->authhost.sin_family = AF_INET;

	s->debug(1,"Auth host = %s:%d\n",s->authserver,s->authport);
	s->debug(1,"Listening on port %d\n",s->listenport);

	if(login(s))
	{
		s->onconnected(s->listenport);
		if(!handle_heartbeats(s))       
		{
		   /*
		    **   heartbeat return 0: 
		    **   case 1 : login fail-->to sleep for LGIN_CYCLE sec
		    **   case 2 : restart pkt is recv --> no implement: should reset state and do login
		    */
		    
			int i;
			s->ondisconnected(1);
			s->noncritical("Sleeping for %d second\n",LGIN_CYCLE);
			
			for(i=0; i<LGIN_CYCLE; i++)
			{
				if(s->shutdown)
					return 0;
				else
					sleep(1);
			}
		}
		else
		{
			closesocket(s->listensock);
			return 0;
		}
		closesocket(s->listensock);
	}
	else
	{
		int i;
		/* Foxconn added start, zacker, 07/18/2008 */
		if (s->state == STATE_AWAIT_NEG_RESP)
			logout(0, s);
		/* Foxconn added end, zacker, 07/18/2008 */
		
		s->noncritical("Sleeping for %d second\n",LGIN_CYCLE);
		
		for(i=0; i<LGIN_CYCLE; i++)
		{
			if(s->shutdown)
				return 0;
			else
				sleep(1);
		}
		closesocket(s->listensock);
	}
	return 1;
}

