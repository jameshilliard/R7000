# You may select DEPTHs (no indexing), COUNTs (slower) or both (more memory).
#CPPFLAGS += -DAVL_COUNT -DAVL_DEPTH
SRC_PATH=$(shell pwd)
LN ?= ln
INSTALL ?= /usr/bin/install
LDCONFIG ?= arm-brcm-linux-uclibcgnueabi-ldconfig
#tab tseng
AR = arm-brcm-linux-uclibcgnueabi-ar
AS = arm-brcm-linux-uclibcgnueabi-as
CC = arm-brcm-linux-uclibcgnueabi-gcc
CCDEPMODE = depmode=gcc3
CFLAGS = -Os -O2 -DBCMWPA2 -DRESTART_ALL_PROCESSES -D__CONFIG_USBAP__ -DBCMQOS -DBCMWPS -D__CONFIG_EMF__ -DTRAFFIC_MGMT -DPHYMON -DSUPPORT_REMOTE_HTTPS -DINCLUDE_WPS_V20 -DINCLUDE_5G_AUTO_CHANNEL -DOPENDNS_PARENTAL_CONTROL -DINCLUDE_UCP -D__CONFIG_PLC__ -D__CONFIG_URE__ -DPLC -DWPS_LONGPUSH_DISABLE -Os -DLINUX26 -DCONFIG_KERNEL_2_6_36 -I../build/include

#tab tseng

# Some suggestions: (-mcpu= generates i386 compatible code)
CFLAGS += -O2 -fomit-frame-pointer -pipe -w
#CFLAGS = -O2 -fomit-frame-pointer -pipe -march=i586 -Wall -g
#CFLAGS = -O6 -fomit-frame-pointer -pipe -march=i586 -Wall -ansi -pedantic
#CFLAGS = -O6 -fomit-frame-pointer -pipe -march=i686 -Wall -ansi -pedantic
#CFLAGS = -O6 -march=k6 -fforce-mem -fforce-addr -pipe
#CFLAGS = -g -fomit-frame-pointer -pipe -march=i686 -Wall -ansi -pedantic
#CFLAGS = -g -pg -a -pipe -march=i686 -Wall
#LDFLAGS = -s

prefix ?= /usr
libdir ?= $(prefix)/lib
includedir ?= $(prefix)/include
includedir ?=/projects/hnd/tools/linux/hndtools-arm-linux-2.6.36-uclibc-4.5.3/include

PROGRAMS = avlsort setdiff
LIBRARY = libavl.so.1.5

all: $(LIBRARY)

test: $(PROGRAMS)

setdiff: setdiff.o avl.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

avlsort: avlsort.o avl.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)

$(LIBRARY): avl.o
	$(CC) -nostdlib -shared -Wl,-soname,libavl.so.1 $^ -o $@ -lc

clean:
	$(RM) *.o $(PROGRAMS) libavl.*

install: all
	$(INSTALL) -d $(DESTDIR)$(libdir)
	$(INSTALL) avl.h $(DESTDIR)$(includedir)
	$(INSTALL) $(LIBRARY) $(DESTDIR)$(libdir)
	for i in $(LIBRARY); do\
		$(LN) -sf $$i $(DESTDIR)$(libdir)/$${i%.*};\
		$(LN) -sf $${i%.*} $(DESTDIR)$(libdir)/$${i%.*.*};\
	done
	-$(LDCONFIG)

.PHONY: clean install all
.PRECIOUS: %.h %.c
