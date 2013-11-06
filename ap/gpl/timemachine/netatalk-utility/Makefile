include ../../config.mk
include ../../config.in

OBJS+=wol
CFLAGS  += -I. -I$(TOP)/shared -I$(SRCBASE)/include -Wall

all:	$(OBJS)

wol: wol.c
	$(CC) $(CFLAGS) -o $@ $< $(EXTRA_LDFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJS)

install:  wol
	install -d -m0755 $(TARGETDIR)/usr
	install -d -m0755 $(TARGETDIR)/usr/sbin
	install -m0755 wol $(TARGETDIR)/usr/sbin/wol
