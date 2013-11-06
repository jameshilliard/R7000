HOST=arm-linux
SRC_PATH=$(shell pwd)
HOST_COMPILE=$(HOST)-
TOOL_CHAIN_PATH=$(TOOLCHAIN)
export SRC_PATH

PKG_CONFIG_PATH=$(SRC_PATH)/build/usr/lib/pkgconfig
export PKG_CONFIG_PATH
PKG_CONFIG_LIBDIR=$(SRC_PATH)/build/usr/lib/pkgconfig
export PKG_CONFIG_LIBDIR
PKG_INSTall_DIR =$(SRC_PATH)/build
DESTDIR = $(PKG_INSTall_DIR)
export DESTDIR
LDFLAGS += -L$(SRC_PATH)/build/usr/lib
CFLAGS += -I$(SRC_PATH)/build/usr/include
CPPFLAGS += -I$(SRC_PATH)/build/usr/include

export LDFLAGS
export CFLAGS
export CPPFLAGS
PATH := $(PKG_INSTALL_DIR)/usr/lib:$(PATH)
export PATH

SUBDIRS2 += forked-daapd-0.19

SUBDIRS += zlib-1.2.7
SUBDIRS += confuse-2.7
SUBDIRS += libiconv-1.10
SUBDIRS += tre-0.8.0
SUBDIRS += libantlr3c-3.2
SUBDIRS += libgpg-error-1.10
SUBDIRS += gperf-3.0.4
SUBDIRS += sqlite-3.6.22
SUBDIRS += libgcrypt-1.5.0
SUBDIRS += mxml-2.7
SUBDIRS += libevent-1.4.14b-stable
SUBDIRS += avl-0.3.5
SUBDIRS += libunistring-0.9.3
SUBDIRS += alsa-lib-1.0.26
SUBDIRS += libav-0.8.8
SUBDIRS += libdaemon-0.14
SUBDIRS += expat-2.0.1
SUBDIRS += gdbm-1.8.3
SUBDIRS += dbus-1.6.8
SUBDIRS += avahi-0.6.25
#SUBDIRS += libkqueue-1.0.6 
SUBDIRS += forked-daapd-0.19

SUBDIRS2 = dbus-1.6.8
SUBDIRS3 = avahi-0.6.25
SUBDIRS4 = forked-daapd-0.19
SUBDIRS6 = sqlite-3.6.22
SUBDIRS6 = libiconv-1.10
SUBDIRS6 = libunistring-0.9.3
SUBDIRS6 = libevent-1.4.14b-stable
SUBDIRS5 = alsa-lib-1.0.26



all:
	test -d "$(TARGETDIR)" ||  mkdir  "$(TARGETDIR)" 
	test -d "$(TARGETDIR)/usr" ||  mkdir  "$(TARGETDIR)/usr" 
	test -d "$(TARGETDIR)/usr/bin" ||  mkdir  "$(TARGETDIR)/usr/bin" 
	for i in ${SUBDIRS}; do \
		(cd $$i; make && make install) || exit 1; \
	done
	install -m 755 $(SRC_PATH)/forked-daapd-0.19/src/forked-daapd $(TARGETDIR)/usr/bin
	install -m 755 $(SRC_PATH)/start_forked-daapd.sh $(TARGETDIR)/usr/bin

sqlite:
	for i in ${SUBDIRS6}; do \
		(cd $$i; make && make install) || exit 1; \
	done

daapd:
	for i in ${SUBDIRS}; do \
		(cd $$i; make && make install) || exit 1; \
	done
dbus:
	for i in ${SUBDIRS2}; do \
		(cd $$i; make && make install) || exit 1; \
	done

#	cd sqlite-3.6.22; \
	make CFLAGS="-DSQLITE_ENABLE_UNLOCK_NOTIFY";\
	 --includedir=$(DESTDIR) --libdir=$(DESTDImake install
#	./configure --host=$(HOST) CFLAGS=-Os --enable-threadsafe --prefix=/usr;\
	make CFLAGS="-DSQLITE_ENABLE_UNLOCK_NOTIFY";\
	make install
#	cd mxml-2.7; \
	make && make install-libmxml.so.1.5
	touch .conf
make_iserver:
#ifeq ($(PROFILE),WNDR3400)
	cp config_WNDR3400.h source/include/config.h
#endif
	cd source ; make

clean: 

	echo "$(PATH)"
	for i in ${SUBDIRS}; do \
		(cd $$i; make clean) || exit 1; \
	done
	rm -r ./build/*
	
cleansmb: 
	

distclean:
	rm -rf .conf
	cd source ; make distclean

install:
	$(STRIP)  $(SRC_PATH)/build/usr/lib/*.so 
	install -m 755 $(SRC_PATH)/build/usr/lib/*.so  $(TARGETDIR)/lib/
	cp /projects/hnd/tools/linux/hndtools-arm-linux-2.6.36-uclibc-4.5.3/lib/librt* $(TARGETDIR)/lib


		
