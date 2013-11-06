include ../config.mk

ifneq ($(CONFIG_ISERVER),y)
SUBDIRS += gdbm-1.8.3
SUBDIRS += expat-2.0.1
SUBDIRS += libdaemon-0.14
SUBDIRS += libiconv-1.11
#SUBDIRS += gettext-0.17
endif
SUBDIRS += libgpg-error-1.10

ifneq ($(CONFIG_ISERVER),y)
SUBDIRS += avahi-0.6.25
endif
SUBDIRS += libgcrypt-1.5.0
SUBDIRS += zlib-1.2.3
SUBDIRS += db-4.7.25.NC/build_unix
ifneq ($(CONFIG_ISERVER),y)
SUBDIRS += libxml2-2.7.2
endif
SUBDIRS += openssl-0.9.8e
SUBDIRS += netatalk-utility
SUBDIRS += netatalk-2.2.0
ifeq ($(ARCH),arm)
AR = arm-brcm-linux-uclibcgnueabi-ar 
CC = arm-brcm-linux-uclibcgnueabi-gcc
RANLIB = arm-brcm-linux-uclibcgnueabi-ranlib
STRIP = arm-brcm-linux-uclibcgnueabi-strip
else
AR =  mipsel-linux-linux26-ar 
CC =  mipsel-linux-linux26-gcc
RANLIB =  mipsel-linux-linux26-ranlib
STRIP =  mipsel-linux-linux26-strip
endif

TIMEMACHINE_PATH=$(shell pwd)
export TIMEMACHINE_PATH

PKG_INSTALL_DIR=$(TIMEMACHINE_PATH)/build
export PKG_INSTALL_DIR

PATH := $(PKG_INSTALL_DIR)/usr/lib:$(PATH)
export PATH

PKG_CONFIG_PATH=$(PKG_INSTALL_DIR)/usr/lib/pkgconfig
export PKG_CONFIG_PATH
PKG_CONFIG_LIBDIR=$(PKG_INSTALL_DIR)/usr/lib/pkgconfig
export PKG_CONFIG_LIBDIR

DESTDIR = $(PKG_INSTALL_DIR)
export DESTDIR

LDFLAGS += -L$(PKG_INSTALL_DIR)/usr/lib
CFLAGS += -I$(PKG_INSTALL_DIR)/usr/include

export LDFLAGS
export CFLAGS


all: 
	for i in ${SUBDIRS}; do \
		(cd $$i; make all install) || exit 1; \
	done
	
install:
#	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libintl.so.* $(TARGETDIR)/usr/lib/
	install -d -m0755 $(TARGETDIR)/etc/avahi	
	install -d -m0755 $(TARGETDIR)/usr/config/avahi/services
	rm -f $(TARGETDIR)/etc/avahi/services
	ln -s /tmp/avahi/services $(TARGETDIR)/etc/avahi/services
	install -d -m0755 $(TARGETDIR)/etc/init.d
ifneq ($(CONFIG_ISERVER),y)
	install -m0755 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/avahi-daemon.init $(TARGETDIR)/etc/init.d/avahi-daemon	
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libgdbm.so.* $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libexpat.so.* $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libdaemon.so.* $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libiconv.so* $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libgpg-error.so.* $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libavahi-{common,core}.so.* $(TARGETDIR)/usr/lib/
#endif
	cp $(TIMEMACHINE_PATH)/avahi-0.6.25/avahi-autoipd/avahi-autoipd.action $(TARGETDIR)/etc/avahi/
#ifneq ($(CONFIG_ISERVER),y)
	install -m 755 $(PKG_INSTALL_DIR)/usr/sbin/avahi-autoipd $(TARGETDIR)/usr/sbin/
	install -m 755 $(PKG_INSTALL_DIR)/usr/sbin/avahi-daemon $(TARGETDIR)/usr/sbin/
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/avahi-daemon.conf $(TARGETDIR)/etc/avahi/
	install -d -m0755 $(TARGETDIR)/etc/avahi
	cp $(TIMEMACHINE_PATH)/avahi-0.6.25/avahi-dnsconfd/avahi-dnsconfd.action $(TARGETDIR)/etc/avahi/
	install -m 755 $(PKG_INSTALL_DIR)/usr/sbin/avahi-dnsconfd $(TARGETDIR)/usr/sbin/	
endif
ifeq ($(CONFIG_ISERVER),y)
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/afpd.service $(TARGETDIR)/usr/etc/afpd.service
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/service-http $(TARGETDIR)/usr/etc/http.service
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/smbd.service $(TARGETDIR)/usr/etc/smbd.service
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/adisk.service $(TARGETDIR)/usr/etc/adisk.service
else
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/afpd.service $(TARGETDIR)/usr/config/avahi/services/afpd.service
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/service-http $(TARGETDIR)/usr/config/avahi/services/http.service
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/smbd.service $(TARGETDIR)/usr/config/avahi/services/smbd.service
	install -m0644 $(TIMEMACHINE_PATH)/avahi-0.6.25/files/adisk.service $(TARGETDIR)/usr/config/avahi/services/adisk.service
endif
ifneq ($(CONFIG_ISERVER),y)
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libgcrypt.so.* $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libdb-*.so $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libxml2.so $(TARGETDIR)/usr/lib/
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/libxml2.so.* $(TARGETDIR)/usr/lib/
endif
	install -m 755 $(PKG_INSTALL_DIR)/usr/lib/lib{crypto,ssl}.so.* $(TARGETDIR)/usr/lib/
	install -d -m0755 $(TARGETDIR)/usr/lib/uams/
	install -d -m0755 $(TARGETDIR)/etc/netatalk/
	rm -f $(TARGETDIR)/etc/netatalk/AppleVolumes.default
	ln -s /tmp/netatalk/AppleVolumes.default $(TARGETDIR)/etc/netatalk/AppleVolumes.default
	rm -f $(TARGETDIR)/etc/netatalk/afp_signature.conf
	ln -s /tmp/netatalk/afp_signature.conf $(TARGETDIR)/etc/netatalk/afp_signature.conf
	rm -f $(TARGETDIR)/etc/netatalk/afppasswd
	ln -s /tmp/netatalk/afppasswd $(TARGETDIR)/etc/netatalk/afppasswd
	install -d -m0755 $(TARGETDIR)/usr/config/netatalk
	install -m 755 $(TIMEMACHINE_PATH)/netatalk-2.2.0/etc/afpd/afpd $(TARGETDIR)/usr/sbin/
	install -m 755 $(TIMEMACHINE_PATH)/netatalk-2.2.0/bin/afppasswd/afppasswd $(TARGETDIR)/usr/sbin/
	install -m 755 $(TIMEMACHINE_PATH)/netatalk-2.2.0/etc/cnid_dbd/cnid_dbd $(TARGETDIR)/usr/sbin/
	install -m 755 $(TIMEMACHINE_PATH)/netatalk-2.2.0/etc/cnid_dbd/cnid_metad $(TARGETDIR)/usr/sbin/
	install -m 755 $(TIMEMACHINE_PATH)/netatalk-2.2.0/etc/uams/.libs/*.so $(TARGETDIR)/usr/lib/uams/
	rm -f $(TARGETDIR)/usr/lib/uams/uams_dhx.so
	rm -f $(TARGETDIR)/usr/lib/uams/uams_dhx2.so
	ln -s /usr/lib/uams/uams_dhx_passwd.so $(TARGETDIR)/usr/lib/uams/uams_dhx.so
	ln -s /usr/lib/uams/uams_dhx2_passwd.so $(TARGETDIR)/usr/lib/uams/uams_dhx2.so
	cp $(TIMEMACHINE_PATH)/netatalk-2.2.0/files/AppleVolumes.default $(TARGETDIR)/usr/config/netatalk/
	cp $(TIMEMACHINE_PATH)/netatalk-2.2.0/files/AppleVolumes.system $(TARGETDIR)/etc/netatalk/
	install -m0600 $(TIMEMACHINE_PATH)/netatalk-2.2.0/files/afpd.conf $(TARGETDIR)/etc/netatalk/
	install -m0755 $(TIMEMACHINE_PATH)/netatalk-2.2.0/files/afpd.init $(TARGETDIR)/etc/init.d/afpd
	install -m0755 $(TIMEMACHINE_PATH)/netatalk-2.2.0/files/detach_afp_shares $(TARGETDIR)/usr/sbin/detach_afp_shares
	rm -f $(TARGETDIR)/etc/shadow
	rm -f $(TARGETDIR)/etc/shadow+
	ln -s /tmp/config/shadow $(TARGETDIR)/etc/shadow
	ln -s /tmp/config/shadow+ $(TARGETDIR)/etc/shadow+
	install -m0755 $(TIMEMACHINE_PATH)/netatalk-utility/wol $(TARGETDIR)/usr/sbin/wol

clean:
	for i in ${SUBDIRS}; do \
		(cd $$i; make clean); \
	done
