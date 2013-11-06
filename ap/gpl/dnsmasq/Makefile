include ../config.in
include ../config.mk

OBJS = cache.o rfc1035.o dhcp.o util.o option.o forward.o network.o dnsmasq.o
BINDIR = $(TARGETDIR)/usr/sbin
MANDIR = $(TARGETDIR)/usr/man

all : dnsmasq

clean :
	rm -f *~ $(OBJS) dnsmasq
	rm -f $(BINDIR)/dnsmasq

.c.o: dnsmasq.h
	$(CC) -O2 -Wall -W -c $*.c 


dnsmasq : $(OBJS) dnsmasq.h config.h
	$(CC) -o $@  $(OBJS) $(LIBS)

install : dnsmasq
	install -d $(BINDIR)
#	install -m 644 dnsmasq.8 $(MANDIR)/man8 
	install -m 755 dnsmasq $(BINDIR)
	$(STRIP) $(BINDIR)/dnsmasq




