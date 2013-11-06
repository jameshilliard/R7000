#
# PPPoEcd Makefile
#
# Copyright (C) 2012, Broadcom Corporation. All Rights Reserved.
# 
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
# OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# $Id: Makefile 247606 2011-03-21 05:53:04Z $
# 

# Uncomment the following line to enable CCP compression
# CCP_SUPPORT=y

# Uncomment the following line to enable standard CHAP authentication
CHAP_SUPPORT=y

# Uncomment the following line to enable MS CHAP authentication
CHAPMS_SUPPORT=y

# Uncomment the following to enable debugging
# DFLAGS	+= -g -DDEBUG

CFLAGS	:= -D_linux_=1 -DHAVE_PATHS_H -DHAVE_MMAP
CFLAGS	+= -I. -I../pppd -pipe -Wall
ifeq ($(CONFIG_RTR_OPTIMIZE_SIZE),y)
CFLAGS  += -Os
else
CFLAGS  += -O2
endif
CFLAGS	+= $(DFLAGS)

vpath	%.c ../pppd
OBJS	:= magic.o fsm.o lcp.o ipcp.o upap.o
vpath	%.c ../pppd/plugins/pppoe
OBJS	+= pppoehash.o pppoe_client.o libpppoe.o
OBJS	+= main.o auth.o options.o demand.o utils.o sys-linux.o pppoe.o

ifdef CCP_SUPPORT
CFLAGS	+= -DCCP_SUPPORT=1
OBJS	+= ccp.o
endif

ifdef CHAP_SUPPORT
CFLAGS	+= -DCHAP_SUPPORT=1
OBJS	+= md5.o chap.o
endif

ifdef CHAPMS_SUPPORT
CFLAGS	+= -DCHAPMS=1 -DUSE_CRYPT=1 -DHAVE_CRYPT_H=1
OBJS	+= md4.o chap_ms.o
endif

ifneq ($(wildcard $(LIBDIR)/libcrypt.a),)
LIBCRYPT := $(LIBDIR)/libcrypt.a
else
LIBCRYPT := $(USRLIBDIR)/libcrypt.a
endif

all: pppoecd

install: all
	install -d $(INSTALLDIR)/usr/sbin
	install -m 755 pppoecd $(INSTALLDIR)/usr/sbin
	$(STRIP) $(INSTALLDIR)/usr/sbin/pppoecd

pppoecd: $(OBJS)
	$(LD) -r -o .$@ $^ $(LIBCRYPT)
	$(CC) -o $@ .$@
	rm -f .$@

clean:
	rm -f *.o pppoecd
